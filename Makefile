# ============================================================
#  Makefile — Shikaku
# ============================================================

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET   = shikaku

SRCS     = shikaku.cxx interfaz.cxx tablero.cxx solucionador.cxx
OBJS     = $(SRCS:.cxx=.o)

# ------------------------------------------------------------
#  Regla principal: compilar todo
# ------------------------------------------------------------
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# ------------------------------------------------------------
#  Reglas por archivo objeto
# ------------------------------------------------------------
shikaku.o: shikaku.cxx interfaz.h
	$(CXX) $(CXXFLAGS) -c shikaku.cxx

interfaz.o: interfaz.cxx interfaz.h tablero.h solucionador.h
	$(CXX) $(CXXFLAGS) -c interfaz.cxx

tablero.o: tablero.cxx tablero.h
	$(CXX) $(CXXFLAGS) -c tablero.cxx

solucionador.o: solucionador.cxx solucionador.h tablero.h
	$(CXX) $(CXXFLAGS) -c solucionador.cxx

# ------------------------------------------------------------
#  Ejecutar el juego directamente con: make run
# ------------------------------------------------------------
run: all
	./$(TARGET)

# ------------------------------------------------------------
#  Limpiar archivos generados
# ------------------------------------------------------------
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean