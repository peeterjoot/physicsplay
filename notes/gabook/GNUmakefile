THISDIR := gabook

include ../make.vars

SOURCE_DIRS += appendix
SOURCE_DIRS += basics
SOURCE_DIRS += calculus
SOURCE_DIRS += electrodynamics
SOURCE_DIRS += emstress
SOURCE_DIRS += figures
SOURCE_DIRS += fourier
SOURCE_DIRS += lagrangian
SOURCE_DIRS += lorentzforce
SOURCE_DIRS += mathematica
SOURCE_DIRS += physics
SOURCE_DIRS += projection
SOURCE_DIRS += qm
SOURCE_DIRS += relativity
SOURCE_DIRS += rotation

ORIG_FILES += ../algebra/levi.pl

ORIG_FIGURE_DIRS += ../calculus
ORIG_FIGURE_DIRS += ../differential_forms
ORIG_FIGURE_DIRS += ../geometric-algebra
ORIG_FIGURE_DIRS += ../miscphysics/figures

LOCAL_FIGURE_FILES += Projection_line.png
LOCAL_FIGURE_FILES += Projection_plane.png
LOCAL_FIGURE_FILES += bivectorDot.png
LOCAL_FIGURE_FILES += charge_line_element_figure.png
LOCAL_FIGURE_FILES += cube_unfolded_004.png
LOCAL_FIGURE_FILES += imaginaryorientation.png
LOCAL_FIGURE_FILES += normalRot.png
LOCAL_FIGURE_FILES += p41.png
LOCAL_FIGURE_FILES += parallelogram_parameterized.png
LOCAL_FIGURE_FILES += parallelogramvec.png
LOCAL_FIGURE_FILES += parallelopiped_parameterized.png
LOCAL_FIGURE_FILES += planeParameterization.png
LOCAL_FIGURE_FILES += planerejection.png
LOCAL_FIGURE_FILES += rotationGen.png
LOCAL_FIGURE_FILES += rotor.png
LOCAL_FIGURE_FILES += satellite.png
LOCAL_FIGURE_FILES += spherical_polar.png
LOCAL_FIGURE_FILES += surface_area_element.png
LOCAL_FIGURE_FILES += surface_flux_element.png
LOCAL_FIGURE_FILES += tangent_area_form.png
LOCAL_FIGURE_FILES += visualize_subspace_projection.png
LOCAL_FIGURE_FILES += volume_element.png

LOCAL_FIGURE_FILES := $(addprefix figures/,$(LOCAL_FIGURE_FILES))

GENERATED_SOURCES += mathematica.tex 
GENERATED_SOURCES += cronology.tex

include ../make.rules

figures/%.png: %.png
	cp $< $@

vpath %.png $(ORIG_FIGURE_DIRS)
