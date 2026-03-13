#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(git -C "$SCRIPT_DIR" rev-parse --show-toplevel)"

INCLUDE_DIR="$REPO_ROOT/tql/include/tensor/tql"
SRC_DIR="$REPO_ROOT/tql/src"

echo "→ Cleaning generated sources..."
rm -rf "$SCRIPT_DIR/src"
mkdir -p "$SCRIPT_DIR/src"

echo "→ Running ANTLR4..."
java -jar "$SCRIPT_DIR/antlr-4.13.2-complete.jar" \
  -Dlanguage=Cpp \
  -visitor \
  -no-listener \
  -o "$SCRIPT_DIR/src/" \
  "$SCRIPT_DIR/TQLLexer.g4" \
  "$SCRIPT_DIR/TQLParser.g4"

echo "→ Creating destination directories..."
mkdir -p "$INCLUDE_DIR" "$SRC_DIR"

echo "→ Copying headers..."
cp "$SCRIPT_DIR/src/TQLLexer.h"             "$INCLUDE_DIR/"
cp "$SCRIPT_DIR/src/TQLParser.h"            "$INCLUDE_DIR/"
cp "$SCRIPT_DIR/src/TQLParserVisitor.h"     "$INCLUDE_DIR/"
cp "$SCRIPT_DIR/src/TQLParserBaseVisitor.h" "$INCLUDE_DIR/"

echo "→ Copying sources..."
cp "$SCRIPT_DIR/src/TQLLexer.cpp"             "$SRC_DIR/"
cp "$SCRIPT_DIR/src/TQLParser.cpp"            "$SRC_DIR/"
cp "$SCRIPT_DIR/src/TQLParserVisitor.cpp"     "$SRC_DIR/"
cp "$SCRIPT_DIR/src/TQLParserBaseVisitor.cpp" "$SRC_DIR/"

echo "✓ Done."
echo "  headers → $INCLUDE_DIR"
echo "  sources → $SRC_DIR"