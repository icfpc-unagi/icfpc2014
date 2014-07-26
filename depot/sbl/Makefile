all:
	pwd="$$(pwd)"; cd "$${pwd%/depot/*}"; \
	    target="depot/$${pwd##*/depot/}/..."; make "$${target}"
.PHONY: all
