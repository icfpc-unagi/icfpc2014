import static java.util.Arrays.*;

import java.io.*;
import java.util.*;

public class BCompiler {
	
	@SetOpt.Option(abbr = 'r', usage = "runを呼ぶモード")
	public boolean run = false;
	
	@SetOpt.Option(abbr = 'l', usage = "ライブラリコンパイルモード(エントリなし，ラベル付き出力)")
	public boolean lib = false;
	
	int q;
	Map<String, Integer> numVars;
	ArrayList<String> globalVars;
	Map<String, Function> functions;
	
	class Function {
		boolean isVoid;
		String name;
		String[] args;
		Block block;
		Function(boolean isVoid, String name, String[] args, Block block) {
			this.isVoid = isVoid;
			this.name = name;
			this.args = args;
			this.block = block;
		}
		@Override
		public String toString() {
			return String.format("%s(%s)", name, Arrays.toString(args));
		}
	}
	
	abstract class Exp {
	}
	
	class Op2 extends Exp {
		String op;
		Exp left, right;
		Op2(String op, Exp left, Exp right) {
			this.op = op;
			this.left = left;
			this.right = right;
			if (op.equals("<")) {
				this.op = ">";
				this.left = right;
				this.right = left;
			} else if (op.equals("<=")) {
				this.op = ">=";
				this.left = right;
				this.right = left;
			}
		}
	}
	
	class Const extends Exp {
		int val;
		Const(int val) {
			this.val = val;
		}
	}
	
	class Var extends Exp {
		String name;
		Var(String name) {
			this.name = name;
		}
	}
	
	class Apply extends Exp {
		String name;
		Exp[] args;
		Apply(String name, Exp[] args) {
			this.name = name;
			this.args = args;
		}
	}
	
	class Block {
		String[] vars;
		Code[] codes;
		Block(String[] vars, Code[] codes) {
			this.vars = vars;
			this.codes = codes;
		}
	}
	
	abstract class Code {
	}
	
	class While extends Code {
		Exp cond;
		Block block;
		While(Exp cond, Block block) {
			this.cond = cond;
			this.block = block;
		}
	}
	
	class If extends Code {
		Exp cond;
		Block thenBlock, elseBlock;
		If(Exp cond, Block thenBlock, Block elseBlock) {
			this.cond = cond;
			this.thenBlock = thenBlock;
			this.elseBlock = elseBlock;
		}
	}
	
	class Assign extends Code {
		String var;
		Exp exp;
		Assign(String var, Exp exp) {
			this.var = var;
			this.exp = exp;
		}
	}
	
	class Return extends Code {
		Exp exp;
		Return(Exp exp) {
			this.exp = exp;
		}
	}
	
	Exp getExp(Parser p) {
		Exp t = getExp2(p);
		while (p.peek() == '<' || p.peek() == '>' || p.peek() == '=') {
			String c = "" + ((char)p.peek());
			p.p++;
			if (p.p < p.cs.length && p.cs[p.p] == '=') {
				c += "=";
				p.p++;
			}
			t = new Op2(c, t, getExp2(p));
		}
		return t;
	}
	
	Exp getExp2(Parser p) {
		Exp t = getFactor(p);
		while (p.peek() == '+' || p.peek() == '-') {
			String c = "" + ((char)p.peek());
			p.p++;
			t = new Op2(c, t, getFactor(p));
		}
		return t;
	}
	
	Exp getFactor(Parser p) {
		Exp t = getTerm(p);
		while (p.peek() == '*' || p.peek() == '/') {
			String c = "" + ((char)p.peek());
			p.p++;
			t = new Op2(c, t, getTerm(p));
		}
		return t;
	}
	
	Exp getTerm(Parser p) {
		if (p.peek() == '(') {
			p.p++;
			Exp t = getExp(p);
			if (p.peek() != ')') throw p.new ParseException("expected: ), actual: " + p.peek());
			p.p++;
			return t;
		} else if (p.peek() >= '0' && p.peek() <= '9') {
			int t = 0;
			while (p.peek() >= '0' && p.peek() <= '9') {
				t = t * 10 + p.peek() - '0';
				p.p++;
			}
			return new Const(t);
		} else if (p.peek() == '-') {
			p.p++;
			Exp e = getTerm(p);
			if (e instanceof Const) return new Const(-((Const) e).val);
			return new Op2("-", new Const(0), e);
		} else {
			String name = p.readName();
			if (p.peek() == '(') {
				p.p++;
				ArrayList<Exp> args = new ArrayList<Exp>();
				while (p.peek() != ')') {
					if (args.size() > 0) p.eat(',');
					args.add(getExp(p));
				}
				p.eat(')');
				return new Apply(name, args.toArray(new Exp[0]));
			} else {
				return new Var(name);
			}
		}
	}
	
	Block getBlock(Parser p) {
		ArrayList<String> vars = new ArrayList<String>();
		ArrayList<Code> codes = new ArrayList<Code>();
		while ((p.peek() == 'i' && p.cs[p.p + 1] == 'n' || p.peek() == 'P')) {
			p.readType();
			vars.add(p.readName());
			p.eat(';');
		}
		while (p.peek() != '}') {
			int q = p.p;
			String name = p.readName();
			if (name.equals("return")) {
				if (p.peek() == ';') throw p.new ParseException("Illegal return");
				codes.add(new Return(getExp(p)));
				p.eat(';');
			} else if (name.equals("if")) {
				p.eat('(');
				Exp cond = getExp(p);
				p.eat(')');
				p.eat('{');
				Block thenBlock = getBlock(p);
				p.eat('}');
				int pp = p.p;
				if (!p.readName().equals("else")) {
					p.p = pp;
					codes.add(new If(cond, thenBlock, new Block(new String[0], new Code[0])));
				} else {
					p.eat('{');
					Block elseBlock = getBlock(p);
					p.eat('}');
					codes.add(new If(cond, thenBlock, elseBlock));
				}
			} else if (name.equals("while")) {
				p.eat('(');
				Exp cond = getExp(p);
				p.eat(')');
				p.eat('{');
				Block block = getBlock(p);
				p.eat('}');
				codes.add(new While(cond, block));
			} else {
				char op = 0;
				if (p.peek() == '(') {
					p.p = q;
					name = null;
				} else {
					if (p.peek() == '+') {
						op = '+';
						p.eat('+');
					} else if (p.peek() == '-') {
						op = '-';
						p.eat('-');
					}
					p.eat('=');
				}
				if (op != 0) {
					codes.add(new Assign(name, new Op2("" + op, new Var(name), getExp(p))));
				} else {
					codes.add(new Assign(name, getExp(p)));
				}
				p.eat(';');
			}
		}
		return new Block(vars.toArray(new String[0]), codes.toArray(new Code[0]));
	}
	
	Function[] getFunctions(Parser p) {
		ArrayList<Function> funcs = new ArrayList<BCompiler.Function>();
		while (!p.isEOF()) {
			boolean isVoid = p.peek() == 'v';
			p.readType();
			String name = p.readName();
			if (p.peek() != '(') {
				p.eat(';');
				globalVars.add(name);
			} else {
				p.eat('(');
				ArrayList<String> args = new ArrayList<String>();
				while (p.peek() != ')') {
					if (args.size() > 0) p.eat(',');
					p.readType();
					args.add(p.readName());
				}
				p.eat(')');
				p.eat('{');
				Block block = getBlock(p);
				p.eat('}');
				if (run && name.equals("run") || !run && (name.equals("init") || name.equals("step"))) {
					if (block.vars.length > 0) {
						throw new RuntimeException("function " + name + " cannot have local vars");
					}
				}
				funcs.add(new Function(isVoid, name, args.toArray(new String[0]), block));
			}
		}
		return funcs.toArray(new Function[0]);
	}
	
	String getOp(String op) {
		if (op.equals("+")) return "ADD";
		if (op.equals("-")) return "SUB";
		if (op.equals("*")) return "MUL";
		if (op.equals("/")) return "DIV";
		if (op.equals("==")) return "CEQ";
		if (op.equals(">")) return "CGT";
		if (op.equals(">=")) return "CGTE";
		throw null;
	}
	
	void toGCC(Exp e, Map<String, int[]> vars, int depth, ArrayList<String> list) {
		if (e instanceof Const) {
			list.add(String.format("LDC %d", ((Const) e).val));
		} else if (e instanceof Op2) {
			toGCC(((Op2) e).left, vars, depth, list);
			toGCC(((Op2) e).right, vars, depth, list);
			list.add(getOp(((Op2) e).op));
		} else if (e instanceof Apply) {
			if (numVars.containsKey(((Apply) e).name)) {
				for (Exp a : ((Apply) e).args) {
					toGCC(a, vars, depth, list);
				}
				int m = numVars.get(((Apply) e).name);
				for (int i = 0; i < m; i++) {
					list.add("LDC 0");
				}
				list.add(String.format("LD %d @%s", depth, ((Apply) e).name));
				list.add(String.format("AP %d", ((Apply) e).args.length + m));
			} else {
				String name = ((Apply) e).name;
				if (name.equals("P")) {
					if (((Apply) e).args.length != 2) throw new RuntimeException("Illegal arguments: " + name);
					toGCC(((Apply) e).args[0], vars, depth, list);
					toGCC(((Apply) e).args[1], vars, depth, list);
					list.add("CONS");
				} else if (name.equals("fst")) {
					if (((Apply) e).args.length != 1) throw new RuntimeException("Illegal arguments: " + name);
					toGCC(((Apply) e).args[0], vars, depth, list);
					list.add("CAR");
				} else if (name.equals("snd")) {
					if (((Apply) e).args.length != 1) throw new RuntimeException("Illegal arguments: " + name);
					toGCC(((Apply) e).args[0], vars, depth, list);
					list.add("CDR");
				} else if (name.equals("toi") || name.equals("top")) {
					if (((Apply) e).args.length != 1) throw new RuntimeException("Illegal arguments: " + name);
					toGCC(((Apply) e).args[0], vars, depth, list);
				} else if (name.equals("atom")) {
					if (((Apply) e).args.length != 1) throw new RuntimeException("Illegal arguments: " + name);
					toGCC(((Apply) e).args[0], vars, depth, list);
					list.add("ATOM");
				} else if (name.equals("debug")) {
					if (((Apply) e).args.length != 1) throw new RuntimeException("Illegal arguments: " + name);
					toGCC(((Apply) e).args[0], vars, depth, list);
					list.add("DBUG");
				} else {
					throw new RuntimeException("unknown function: " + name);
				}
			}
		} else if (e instanceof Var) {
			int[] pos = vars.get(((Var) e).name);
			if (pos == null) throw new RuntimeException("undefined variable: " + ((Var) e).name);
			list.add(String.format("LD %d %d", depth - pos[0], pos[1]));
		} else {
			throw null;
		}
	}
	
	void toGCC(Block b, Map<String, int[]> vars, int depth, ArrayList<String> list, Map<String, String[]> blocks) {
		for (Code c : b.codes) {
			if (c instanceof Return) {
				if (((Return) c).exp != null) {
					toGCC(((Return) c).exp, vars, depth, list);
				}
				list.add("RTN");
			} else if (c instanceof Assign) {
				toGCC(((Assign) c).exp, vars, depth, list);
				if (((Assign) c).var != null) {
					int[] pos = vars.get(((Assign) c).var);
					if (pos == null) throw new RuntimeException("undefined variable: " + ((Assign) c).var);
					list.add(String.format("ST %d %d", depth - pos[0], pos[1]));
				} else {
					Exp e = ((Assign) c).exp;
					if (e instanceof Apply) {
						Function f = functions.get(((Apply) e).name);
						if (f != null && !f.isVoid || f == null && !((Apply) e).name.equals("debug")) {
							throw new RuntimeException("returned value must be assigned: " + ((Apply) e).name);
						}
					} else {
						throw null;
					}
				}
			} else if (c instanceof If) {
				toGCC(((If) c).cond, vars, depth, list);
				list.add(String.format("SEL $$then%d $$else%d", q, q));
				int p = q;
				q++;
				ArrayList<String> list1 = new ArrayList<String>(), list2 = new ArrayList<String>();
				toGCC(((If) c).thenBlock, vars, depth, list1, blocks);
				toGCC(((If) c).elseBlock, vars, depth, list2, blocks);
				list1.add("JOIN");
				list2.add("JOIN");
				blocks.put("$$then" + p, list1.toArray(new String[0]));
				blocks.put("$$else" + p, list2.toArray(new String[0]));
			} else if (c instanceof While) {
				toGCC(((While) c).cond, vars, depth, list);
				list.add(String.format("TSEL $$while%d $$next%d", q, q));
				int p = q;
				q++;
				ArrayList<String> list1 = new ArrayList<String>();
				toGCC(((While) c).block, vars, depth, list1, blocks);
				toGCC(((While) c).cond, vars, depth, list1);
				list1.add(String.format("TSEL $$while%d $$next%d_", p, p));
				blocks.put("$$while" + p, list1.toArray(new String[0]));
			}
		}
	}
	
	void toGCC(Function f, Map<String, String[]> blocks) {
		ArrayList<String> gccs = new ArrayList<String>();
		Map<String, int[]> vars = new TreeMap<String, int[]>();
		for (int i = 0; i < f.args.length; i++) {
			vars.put(f.args[i], new int[]{1, i});
		}
		int depth = 1;
		for (int i = 0; i < globalVars.size(); i++) {
			vars.put(globalVars.get(i), new int[]{0, i});
		}
		if (f.block.vars.length > 0) {
			for (int i = 0; i < f.block.vars.length; i++) {
				vars.put(f.block.vars[i], new int[]{depth, f.args.length + i});
			}
		}
		toGCC(f.block, vars, depth, gccs, blocks);
		if (blocks.containsKey("$" + f.name)) throw null;
		if (f.isVoid) gccs.add("RTN");
		for (int i = 0; i < gccs.size() - 1; i++) if (gccs.get(i).startsWith("RTN")) {
			throw new RuntimeException("return can be appeared only at the end of functions");
		}
		if (!gccs.get(gccs.size() - 1).startsWith("RTN")) {
			throw new RuntimeException("return must be appeared at the end of functions");
		}
		blocks.put("$" + f.name, gccs.toArray(new String[0]));
	}
	
	class Parser {
		int[] lines;
		char[] cs;
		int p;
		Parser(int[] lines, String s) {
			this.lines = lines;
			cs = s.toCharArray();
			p = 0;
		}
		void eat() {
			while (p < cs.length && cs[p] == ' ') p++;
		}
		void eat(char c) {
			eat();
			if (p == cs.length) throw new ParseException("unexpected EOF");
			if (cs[p] != c) throw new ParseException("expected: " + c + ", actual: " + cs[p]);
			p++;
		}
		int peek() {
			eat();
			if (p == cs.length) return -1;
			return cs[p];
		}
		boolean isEOF() {
			eat();
			return p == cs.length;
		}
		void readType() {
			String name = readName();
			if (!name.equals("int") && !name.equals("P") && !name.equals("void")) throw new ParseException("expected: type, actual: " + name);
		}
		String readName() {
			eat();
			if (isEOF()) throw new ParseException("unexpected EOF");
			StringBuilder sb = new StringBuilder();
			while (Character.isJavaIdentifierPart(cs[p])) {
				sb.append(cs[p++]);
			}
			return sb.toString();
		}
		class ParseException extends RuntimeException {
			public ParseException(String msg) {
				super(String.format("%d: %s", p < lines.length ? lines[p] : -1, msg));
			}
		}
	}
	
	
	void run(String[] files) {
		Parser p;
		try {
			StringBuilder sb = new StringBuilder();
			ArrayList<Integer> lines = new ArrayList<Integer>();
			for (String file : files) {
				BufferedReader in = new BufferedReader(new FileReader(file));
				for (int lineID = 1;; lineID++) {
					String line = in.readLine();
					if (line == null) break;
					line = line.trim();
					if (line.startsWith("#")) {
						continue;
					}
					if (line.contains("//")) line = line.substring(0, line.indexOf("//")).trim();
					sb.append(line);
					for (int i = 0; i < line.length(); i++) lines.add(lineID);
				}
				in.close();
			}
			p = new Parser(toi(lines.toArray(new Integer[0])), sb.toString());
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		globalVars = new ArrayList<String>();
		Function[] funcs = getFunctions(p);
		functions = new TreeMap<String, BCompiler.Function>();
		for (Function f : funcs) functions.put(f.name, f);
		if (!lib && run && !functions.containsKey("run")) {
			throw new RuntimeException("need function: run");
		} else if (!lib && !run && !functions.containsKey("init")) {
			throw new RuntimeException("need function: init");
		} else if (!lib && !run && !functions.containsKey("step")) {
			throw new RuntimeException("need function: step");
		}
		numVars = new TreeMap<String, Integer>();
		for (Function f : funcs) numVars.put(f.name, f.block.vars.length);
		q = 0;
		Map<String, String[]> blocks = new TreeMap<String, String[]>();
		for (Function f : funcs) {
			toGCC(f, blocks);
			if (f.name.equals("step")) {
				if (f.block.vars.length > 0) {
					throw new RuntimeException("Illegal Local Variable: " + f.name);
				}
			}
		}
		if (!lib) {
			Map<String, Integer> pos = new TreeMap<String, Integer>();
			ArrayList<String> list = new ArrayList<String>();
			Map<String, Integer> globals = new TreeMap<String, Integer>();
			list.add("DUM " + (globalVars.size() + funcs.length));
			for (int i = 0; i < globalVars.size(); i++) {
				list.add("LDC 0");
			}
			for (int i = 0; i < funcs.length; i++) {
				list.add("LDF $" + funcs[i].name);
				globals.put("@" + funcs[i].name, globalVars.size() + i);
			}
			list.add("LDF " + (list.size() + 3));
			list.add("RAP " + (globalVars.size() + funcs.length));
			list.add("RTN");
			if (!run) {
				list.add("LD 1 0");
				list.add("LD 1 1");
				list.add("LD 0 @init");
				list.add("AP 2");
				list.add("LD 0 @step");
				list.add("CONS");
				list.add("RTN");
			} else {
				list.add("LD 0 @run");
				list.add("AP 0");
				list.add("RTN");
			}
			for (Map.Entry<String, String[]> b : blocks.entrySet()) {
				list.add("BRK ; " + b.getKey());
				pos.put(b.getKey(), list.size());
				for (String s : b.getValue()) {
					list.add(s);
				}
			}
			for (int i = 0; i < list.size(); i++) {
				String ss = list.get(i);
				for (String s : ss.split(" ")) {
					if (s.equals(";")) continue;
					if (s.startsWith("$$next")) {
						if (!s.endsWith("_")) {
							pos.put(s, i + 1);
							pos.put(s + "_", i + 1);
						}
					}
				}
			}
			for (int i = 0; i < list.size(); i++) {
				boolean first = true;
				String t = ";";
				if (!list.get(i).startsWith("BRK")) System.out.print("  ");
				for (String s : list.get(i).split(" ")) {
					if (!first) System.out.print(" ");
					first = false;
					if (s.startsWith("$")) {
						t += " " + s;
						s = "" + pos.get(s);
					}
					if (s.startsWith("@")) s = "" + globals.get(s);
					System.out.print(s);
				}
				if (t.length() > 1) System.out.print(" " + t);
				System.out.println();
			}
		} else {
			for (Map.Entry<String, String[]> b : blocks.entrySet()) {
				String label = b.getKey();
				if (numVars.containsKey(b.getKey())) {
					label += "(" + numVars + ")";
				}
				System.out.println(label + ":");
				for (String s : b.getValue()) {
					System.out.println("  " + s);
				}
			}
		}
	}
	
	int[] toi(Integer[] Is) {
		int n = Is.length;
		int[] is = new int[n];
		for (int i = 0; i < n; i++) is[i] = Is[i];
		return is;
	}
	
	void debug(Object...os) {
		System.err.println(deepToString(os));
	}
	
	public static void main(String[] args) {
		BCompiler b = new BCompiler();
		args = SetOpt.setOpt(b, args);
		b.run(args);
	}
	
}
