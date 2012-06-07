for i in date ; do perl -p -i -e "s/.*"'\\'"$i/%$&/;" *tex ; done
#perl -p -i -e 's/.*useCCL//;' *tex
#for i in blogpage revisionInfo gitRevisionInfo ; do perl -p -i -e "s/.*"'\\'"$i/%$&/;" *tex ; done
#for i in blogpage revisionInfo beginArtWithToc beginArtNoToc EndArticle EndNoBibArticle gitRevisionInfo keywords ; do perl -p -i -e "s/.*"'\\'"$i/%$&/;" *tex ; done
