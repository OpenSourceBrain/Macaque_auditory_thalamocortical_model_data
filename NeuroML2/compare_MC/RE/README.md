`auto_compare.sh` provides the following modes:

- `--pas-nrn`  
  NeuroML vs NEURON, passive (pas-only/leaky) cell.

- `--hh2-nrn`  
  NeuroML vs NEURON, original mechanism (`HH2.mod` → `hh2ad`).

- `--hh2-cnexp-nrn`  
  NeuroML vs NEURON, hh2 with cnexp mechanisms (`hh2_na_cnexp.mod` + `hh2_k_cnexp.mod`, `SUFFIX hh2_na/hh2_k`).

- `--hh2-hh2ad-vs-split`  
  NEURON vs NEURON, direct comparison of `hh2ad` (HH2.mod) vs split `hh2_na+hh2_k` on the same cell.

Usage example (from this directory):

```bash
chmod +x auto_compare.sh

./auto_compare.sh --pas-nrn
./auto_compare.sh --hh2-nrn
./auto_compare.sh --hh2-cnexp-nrn
./auto_compare.sh --hh2-hh2ad-vs-split
```

Notes:

- The NeuroML-based scripts (`run_nml_hh2.py`, `run_nml_leaky.py`, `omv_test.py`) will automatically set `NEURON_HOME` if it is not already defined, by locating `nrniv` on your `PATH`.


In the mod folder, there are the original file HH2.mod, the files hh2_k.mod and hh2_na.mod exported from NeuroML, as well as the modified mod files mod/hh2_na_cnexp.mod and mod/hh2_k_cnexp.mod (the purpose is to demonstrate why the mod files exported from NeuroML cannot be recognized as cnexp format). By using nrnivmodl mod to check the C files, the differences can be observed.

Result: The difference in the leak channel is 0. After incorporating hh2ad, there is a significant numerical discrepancy during action potential generation. While the discrepancy for a single channel may be acceptable, when all ion channels are combined, it leads to the generation of an additional spike.
