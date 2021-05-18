#target: prerequisitos
#	regla para build

APPNAME=goldbach_serial

all: $(APPNAME) $(APPNAME)_asan $(APPNAME)_tsan $(APPNAME)_msan $(APPNAME)_ubsan

$(APPNAME): $(APPNAME).c
	cc -g -Wall -Wextra $(APPNAME).c -o $(APPNAME) -pthread

$(APPNAME)_tsan: $(APPNAME).c
	clang -g -Wall -Wextra -fsanitize=thread $(APPNAME).c -o $(APPNAME)_tsan -pthread

$(APPNAME)_asan: $(APPNAME).c
	clang -g -Wall -Wextra -fsanitize=address $(APPNAME).c -o $(APPNAME)_asan -pthread

$(APPNAME)_msan: $(APPNAME).c
	clang -g -Wall -Wextra -fsanitize=memory $(APPNAME).c -o $(APPNAME)_msan -pthread

$(APPNAME)_ubsan: $(APPNAME).c
	clang -g -Wall -Wextra -fsanitize=undefined $(APPNAME).c -o $(APPNAME)_ubsan -pthread
	
.PHONY: memcheck
memcheck: 
	valgrind ./$(APPNAME)

.PHONY: helgrind
helgrind: 
	valgrind --tool=helgrind --quiet ./$(APPNAME)

.PHONY: rebuild
rebuild: clean $(APPNAME)
	
.PHONY: lint
lint:
	cpplint --filter=-readability/casting $(APPNAME).c
	 
.PHONY: gitignore
gitignore: 
	echo $(APPNAME) $(APPNAME)_asan $(APPNAME)_msan $(APPNAME)_tsan  $(APPNAME)_ubsan | tr " " "\n"> .gitignore

.PHONY: clean 
clean: 
	rm -rf $(APPNAME) $(APPNAME)_asan $(APPNAME)_msan $(APPNAME)_tsan $(APPNAME)_ubsan
	
