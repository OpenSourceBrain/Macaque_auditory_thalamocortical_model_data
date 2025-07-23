#!/usr/bin/env python3
"""
Script to create annotations for various models.

File: create_annotations.py

Copyright 2024 Ankur Sinha
Author: Ankur Sinha <sanjay DOT ankur AT gmail DOT com>
"""


from pyneuroml.annotations import create_annotation


def annotate_():
    """Annotation for channel"""
    annotation = create_annotation(
        subject="cat",
        title="NeuroML conversion of cat channel from Macaque_auditory_thalamocortical_model",
        abstract=None,
        serialization_format="pretty-xml",
        annotation_style="miriam",
        indent=12,
        xml_header=False,
        description="T-calcium channel",
        creation_date="2025-07-24",
        #citations={"https://www.pnas.org/doi/10.1073/pnas.1216867110": "PNAS"},
        sources={"http://senselab.med.yale.edu/modeldb/ShowModel.asp?model=126814": "modeldb"},
        #predecessors={"http://senselab.med.yale.edu/modeldb/ShowModel.asp?model=3263&file=\ca3_db\cal2.mod": "Original model"},
        contributors={"Hengye Zhu": {"gluciferd at gmail.com": "email"}}
    )
    print(annotation)

if __name__ == "__main__":
    annotate_()
