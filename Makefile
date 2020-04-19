TARGET = seidel

CXXFLAGS = -Wall -O2 -flto

SRCS = src/potential.cpp src/update_gauss_seidel.cpp src/electric_field.cpp \
       src/initialise_boundary.cpp src/relax.cpp src/gs.cpp src/translate_y.cpp \
       src/parse.cpp src/main.cpp
OBJS = $(subst .cpp,.o,$(SRCS))
HDRS = $(filter-out src/main.hpp, $(subst .cpp,.hpp,$(SRCS))) src/arguments.hpp

all: $(TARGET)
	$(info)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

.PHONY: clean
clean:
	@$(RM) -v $(OBJS)

.PHONY: cleanall
cleanall: clean
	@$(RM) -v $(TARGET)

.PHONY: delete
delete:
	@$(RM) -v u.dat e_x.dat e_y.dat cs.dat

.PHONY: tar
tar:
	@tar -cvJf $(TARGET).tar.xz makefile $(SRCS) $(HDRS)

.PHONY: lint
lint:
	@clang-tidy $(HDRS) $(SRCS)

