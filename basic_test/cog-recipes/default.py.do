mkdir -p $(dirname $1)

# TODO: This triggers an assert error in redo, using redo-stamp hack for now
#redo-ifchange "../source-tree/../cog-recipes/$1.py"

cp "../source-tree/../cog-recipes/$1.py" $3
echo $3 | redo-stamp
redo-always
