# Test has to 'build' these by installing them from the parent dir.
to_install=""
for i in $(find source-tree/../cog-recipes -name '*.py'); do
    to_install="$to_install ${i#source-tree/../}"
done

redo-ifchange $to_install

redo-ifchange bin/test
exec bin/test
