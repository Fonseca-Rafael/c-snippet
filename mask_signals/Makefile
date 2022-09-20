.PHONY=clean all

EXEC=mask_sign

all: $(EXEC)
	$(info ==> build done for $(EXEC))

clean:
	-rm -f *.o $(EXEC)

mask_sign: mask_sign.c
	$(call color_echo,$@:,$(CC),$(CPPFLAGS) $(CFLAGS),$(INC),$^,$(LIB))
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ -o $@ $(LIB)

# colors
define color_echo
	@tput setaf 3
	@echo -n $1" " 
	@tput setaf 4
	@echo -n $2" "
	@tput setaf 7
	@echo -n $3" "
	@tput setaf 5
	@echo -n $4" "
	@tput setaf 11
	@echo -n $5" "
	@tput setaf 5
	@echo $6
	@tput sgr0
endef

