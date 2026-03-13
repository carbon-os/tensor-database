for f in tql/tests/scripts/*.tql; do
    echo ""; ./build/tql/tql-test "$f"
done