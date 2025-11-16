#!/usr/bin/env bash
set -euo pipefail

usage() {
  cat <<'USAGE'
Usage: ./auto_compare.sh [--pas-nrn | --hh2-nrn | --hh2-cnexp-nrn | --hh2-hh2ad-vs-split] [--help]

Options:
  --pas-nrn              Run passive (pas) NEURON (Python) vs NeuroML comparison
  --hh2-nrn              Run hh2 (Traub Na/K, HH2.mod) NEURON (Python) vs NeuroML comparison
  --hh2-cnexp-nrn        Run hh2 (Na/K split cnexp: hh2_na_cnexp/hh2_k_cnexp) NEURON (Python) vs NeuroML comparison
  --hh2-hh2ad-vs-split   Run NEURON hh2ad (HH2.mod) vs split hh2_na+hh2_k comparison
  -h, --help             Show this help
USAGE
}

run_hh2_nrn() {
  echo "[NRN-HH2 1/4] Compile mechanisms from mod/ (HH2.mod -> hh2ad)"
  rm -rf x86_64 || true
  nrnivmodl mod

  echo "[NRN-HH2 2/4] Running pure NEURON (Python) hh2 (dt=0.025 ms)"
  python3 run_neuron_hh2.py

  echo "[NRN-HH2 3/4] Running NeuroML hh2 (dt=0.025 ms)"
  python3 run_nml_hh2.py

  echo "[NRN-HH2 4/4] Comparing traces (high-res, step-aligned)"
  python3 compare_neuron_nml_hh2.py

  echo "[NRN-HH2] Done. See compare_out/hh2_neuron_vs_nml for outputs."
}

run_hh2_cnexp_nrn() {
  echo "[NRN-HH2-CNEXP 1/4] Compile mechanisms from mod/ (hh2_na_cnexp.mod, hh2_k_cnexp.mod, HH2.mod)"
  rm -rf x86_64 || true
  nrnivmodl mod

  echo "[NRN-HH2-CNEXP 2/4] Running pure NEURON (Python) hh2 cnexp split (dt=0.025 ms)"
  python3 run_neuron_hh2_cnexp.py

  echo "[NRN-HH2-CNEXP 3/4] Running NeuroML hh2 (dt=0.025 ms)"
  python3 run_nml_hh2.py

  echo "[NRN-HH2-CNEXP 4/4] Comparing traces (high-res, step-aligned)"
  python3 compare_neuron_nml_hh2_cnexp.py

  echo "[NRN-HH2-CNEXP] Done. See compare_out/hh2_cnexp_neuron_vs_nml for outputs."
}

run_pas_nrn() {
  echo "[NRN-PAS 1/3] Running pure NEURON (Python) passive (dt=0.025 ms)"
  python3 run_neuron_pas.py

  echo "[NRN-PAS 2/3] Running NeuroML leaky (dt=0.025 ms)"
  python3 run_nml_leaky.py

  echo "[NRN-PAS 3/3] Comparing traces (high-res, step-aligned)"
  python3 compare_neuron_nml_pas.py

  echo "[NRN-PAS] Done. See compare_out/leaky_neuron_vs_nml for outputs."
}

run_hh2_hh2ad_vs_split() {
  echo "[RE hh2 hh2ad vs (hh2_na+hh2_k) 1/4] Compiling NEURON mechanisms (mod/hh2_na.mod, mod/hh2_k.mod, HH2.mod, pas_nml2.mod, etc.)"
  rm -rf x86_64 || true
  nrnivmodl mod

  echo "[RE hh2 hh2ad vs (hh2_na+hh2_k) 2/4] Running NEURON hh2ad (HH2.mod, dt=0.025 ms)"
  python3 run_neuron_hh2.py

  echo "[RE hh2 hh2ad vs (hh2_na+hh2_k) 3/4] Running NEURON split hh2 (hh2_na+hh2_k, dt=0.025 ms)"
  python3 run_neuron_hh2_split.py

  echo "[RE hh2 hh2ad vs (hh2_na+hh2_k) 4/4] Comparing mechanisms and generating plots"
  python3 compare_neuron_hh2_hh2ad_vs_split.py

  echo "[RE hh2 hh2ad vs (hh2_na+hh2_k)] Done. See compare_out/hh2_hh2ad_vs_split_neuron for results."
}

main() {
  case "${1-}" in
    --pas-nrn)
      run_pas_nrn
      ;;
    --hh2-nrn)
      run_hh2_nrn
      ;;
    --hh2-cnexp-nrn)
      run_hh2_cnexp_nrn
      ;;
    --hh2-hh2ad-vs-split)
      run_hh2_hh2ad_vs_split
      ;;
    -h|--help|"")
      usage
      ;;
    *)
      echo "Unknown option: $1" >&2
      usage
      exit 1
      ;;
  esac
}

main "$@"
