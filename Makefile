CC	= g++
CFLAGS	= -Wall -std=c++11 -I include/
LFLAGS	= -std=c++11 -I include/ -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system
LINKER	= g++ -o

TARGET	= lc-explorer
SRCDIR	= src
OBJDIR	= obj
HEADIR	= include
BINDIR	= bin
TEXDIR	= tex
TEXNAM	= report.tex

SOURCES		:= $(wildcard $(SRCDIR)/*.cpp)
INCLUDES	:= $(wildcard $(HEADIR)/*.h)
OBJECTS		:= $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS) 
	@$(LINKER) $@ $(OBJECTS) $(LFLAGS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(INCLUDES)
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

clean:
	@rm -rf $(OBJECTS)
	@rm -rf $(BINDIR)/$(TARGET)
	@echo "Cleaned working directory"

tex:
	@pdflatex -shell-escape -synctex=1 -interaction=nonstopmode -output-directory=$(TEXDIR) $(TEXDIR)/$(TEXNAM)
	@echo "Compiled TeX file to PDF"

.PHONY:	all clean tex
