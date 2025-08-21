# Makefile pour Simple Shell
# Holberton School Project

# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=gnu89
TARGET = hsh
SOURCES = main.c shell.c execute.c path.c split.c
OBJECTS = $(SOURCES:.c=.o)

# Règles par défaut
all: $(TARGET)

# Compilation du programme principal
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Compilation des fichiers objets
%.o: %.c shell.h
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(TARGET)

# Recompilation complète
re: fclean all

# Installation (optionnel)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Variables d'environnement pour les tests
test: $(TARGET)
	@echo "=== Test du shell ==="
	@echo "Test 1: Commande exit simple"
	@echo "exit" | ./$(TARGET)
	@echo "Test 2: Commande exit avec code"
	@echo "exit 42" | ./$(TARGET)

# Aide
help:
	@echo "Commandes disponibles:"
	@echo "  all     - Compile le shell"
	@echo "  clean   - Supprime les fichiers objets"
	@echo "  fclean  - Supprime tout"
	@echo "  re      - Recompile tout"
	@echo "  test    - Lance des tests basiques"
	@echo "  help    - Affiche cette aide"

.PHONY: all clean fclean re install test help
