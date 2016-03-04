THISDIR := peterlue
THISBOOK := $(THISDIR)

include ../make.vars

GENERATED_PDFS += AetherPhysics.pdf
GENERATED_PDFS += sampleArticle.pdf

all :: $(GENERATED_PDFS)

$(GENERATED_PDFS) :: $(JUSTBOOKDEPENDENCIES) $(LOCAL_FILES) $(GENERATED_SOURCES) $(COPIED_FILES) $(LOCAL_COPIED_FILES)

include ../make.rules
