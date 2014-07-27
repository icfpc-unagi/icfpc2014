
public class FixedTreeGenerator {
	
	@SetOpt.Option
	public int n = 256;
	
	void run() {
		
	}
	
	public static void main(String[] args) {
		FixedTreeGenerator t = new FixedTreeGenerator();
		args = SetOpt.setOpt(t, args);
		t.run();
	}
	
}
