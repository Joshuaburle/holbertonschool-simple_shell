#!/bin/bash

echo "=== TESTS DU SHELL SIMPLE ==="
echo

echo "Test 1: Commande avec chemin complet (/bin/ls)"
echo "/bin/ls" | ./shell
echo

echo "Test 2: Commande sans chemin (ls - doit échouer)"
echo "ls" | ./shell
echo

echo "Test 3: Commande inexistante"
echo "commandeinexistante" | ./shell
echo

echo "Test 4: Commande exit (doit échouer)"
echo "exit" | ./shell
echo

echo "Test 5: Autre commande avec chemin complet (/bin/pwd)"
echo "/bin/pwd" | ./shell
echo

echo "Test 6: Compilation"
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o shell
if [ $? -eq 0 ]; then
    echo "✅ Compilation réussie"
else
    echo "❌ Erreur de compilation"
fi

echo
echo "=== TESTS TERMINÉS ==="
