all :: gabook.pdf

include make.dep

# logically symlinks, but MikTex doesn't like those:
ORIG_FILES += ../geometric-algebra/Projection_line.png
ORIG_FILES += ../geometric-algebra/Projection_plane.png
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../calculus/bivectorDot.png
ORIG_FILES += ../geometric-algebra/charge_line_element_figure.png
ORIG_FILES += ../geometric-algebra/cube_unfolded_004.png
ORIG_FILES += ../geometric-algebra/imaginaryorientation.png
ORIG_FILES += ../algebra/levi.pl
ORIG_FILES += ../myrefs.bib
ORIG_FILES += ../geometric-algebra/normalRot.png
ORIG_FILES += ../geometric-algebra/p41.png
ORIG_FILES += ../geometric-algebra/parallelogram_parameterized.png
ORIG_FILES += ../geometric-algebra/parallelogramvec.png
ORIG_FILES += ../geometric-algebra/parallelopiped_parameterized.png
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../geometric-algebra/planeParameterization.png
ORIG_FILES += ../geometric-algebra/planerejection.png
ORIG_FILES += ../calculus/rotationGen.png
ORIG_FILES += ../geometric-algebra/rotor.png
ORIG_FILES += ../geometric-algebra/satellite.PNG
ORIG_FILES += ../geometric-algebra/spherical_polar.png
ORIG_FILES += ../calculus/surface_area_element.png
ORIG_FILES += ../geometric-algebra/surface_flux_element.png
ORIG_FILES += ../differential_forms/tangent_area_form.png
ORIG_FILES += ../unsrturl.bst
ORIG_FILES += ../geometric-algebra/visualize_subspace_projection.png
ORIG_FILES += ../calculus/volume_element.png
ORIG_FILES += ../blogit/newtonsIntersectionHorizontal.png
ORIG_FILES += ../blogit/newtonsIntersectionAnyOrientation.png
ORIG_FILES += ../blogit/newtonsIntersectionTwoCurves.png
ORIG_FILES += ../blogit/toriodalSegment.png

LOCAL_FILES := $(notdir $(ORIG_FILES))

$(LOCAL_FILES) : 
	cp $(filter %$@, $(ORIG_FILES)) $@

gabook.pdf :: $(TEXFILES) $(LOCAL_FILES)
	../make_pdflatex main.tex
	mv main.pdf gabook.pdf

cronology.tex : METADATA
	./METADATA -gabook > cronology.tex

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc *.brf $(LOCAL_FILES)
