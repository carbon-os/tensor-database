

$ wget http://www.antlr.org/download/antlr-4.13.2-complete.jar

$ java -jar antlr-4.13.2-complete.jar -Dlanguage=Go -visitor -o ../ DBLexer.g4 DBParser.g4 -no-listener