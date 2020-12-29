.PHONY: all
all:
	@pio run

.PHONY: upload
upload:
	@pio run -t upload

.PHONY: clean
clean:
	@pio run -t clean

.PHONY: test
test:
	@$(MAKE) --no-print-directory -f test.mk
