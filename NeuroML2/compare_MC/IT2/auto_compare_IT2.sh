#!/usr/bin/env bash
set -euo pipefail

usage() {
  cat <<'USAGE'
Usage: ./auto_compare_IT2.sh [--native-vs-netpyne] [--help]

Options:
  --all                Run all single-channel and full-cell comparisons.
  --native-vs-netpyne   Compile IT2 mechanisms, run pure NEURON IT2_reduced,
                        run NetPyNE IT2_reduced, then compare V_soma traces.
  --nml-vs-netpyne      Run NEURON IT2_reduced with NML-fix mechanisms,
                        run NetPyNE IT2_reduced, then compare V_soma traces.
  --kdr-native-vs-nml   Single-channel test: native kdr vs kdr_nml (NEURON vs NEURON).
  --kBK-native-vs-nml   Single-channel test: native kBK vs kBK_nml (NEURON vs NEURON).
  --ih-native-vs-nml    Single-channel test: native ih vs ih_nml (NEURON vs NEURON).
  --nax-native-vs-nml   Single-channel test: native nax vs nax_nml (NEURON vs NEURON).
  --kap-native-vs-nml   Single-channel test: native kap vs kap_nml (NEURON vs NEURON).
  --cal-native-vs-nml   Single-channel test: native cal vs cal_nml (NEURON vs NEURON).
  --can-native-vs-nml   Single-channel test: native can vs can_nml (NEURON vs NEURON).
  --cat-native-vs-nml   Single-channel test: native cat vs cat_nml (NEURON vs NEURON).
  -h, --help            Show this help.

Typical workflow:

  cd IT2
  chmod +x auto_compare_IT2.sh
  ./auto_compare_IT2.sh --native-vs-netpyne

This will:
  1) Run 'nrnivmodl mod' to compile the cleaned IT2 mechanisms.
  2) Run 'python3 run_neuron_IT2_native.py' (pure NEURON).
  3) Run 'python3 IT2_netpy.py' (NetPyNE).
  4) Run 'python3 compare_IT2_native_vs_netpyne.py' to generate plots and stats.
USAGE
}

run_ih_native_vs_nml() {
  echo "[IT2 ih native vs ih_nml 1/4] Compile mechanisms from mod/ (h_kole.mod, ih_nml.mod, pas_nml2.mod, etc.)"
  rm -rf x86_64 || true
  nrnivmodl mod

  echo "[IT2 ih native vs ih_nml 2/4] Running native ih full-geometry test (dt=0.025 ms)"
  python3 run_neuron_ih_native.py

  echo "[IT2 ih native vs ih_nml 3/4] Running ih_nml full-geometry test (dt=0.025 ms)"
  python3 run_neuron_ih_nml.py

  echo "[IT2 ih native vs ih_nml 4/4] Comparing traces (step-aligned in ms)"
  python3 compare/compare_ih_native_vs_nml.py

  echo "[IT2 ih native vs ih_nml] Done. See compare/ih_native_vs_nml for outputs."
}

run_kdr_native_vs_nml() {
  echo "[IT2 kdr native vs kdr_nml 1/4] Compile mechanisms from mod/ (kdr_BS.mod, kdr_nml.mod, pas_nml2.mod, etc.)"
  rm -rf x86_64 || true
  nrnivmodl mod

  echo "[IT2 kdr native vs kdr_nml 2/4] Running native kdr full-geometry test (dt=0.025 ms)"
  python3 run_neuron_kdr_native.py

  echo "[IT2 kdr native vs kdr_nml 3/4] Running kdr_nml full-geometry test (dt=0.025 ms)"
  python3 run_neuron_kdr_nml.py

  echo "[IT2 kdr native vs kdr_nml 4/4] Comparing traces (step-aligned in ms)"
  python3 compare/compare_kdr_native_vs_nml.py

  echo "[IT2 kdr native vs kdr_nml] Done. See compare/kdr_native_vs_nml for outputs."
}

run_kBK_native_vs_nml() {
  echo "[IT2 kBK native vs kBK_nml 1/4] Compile mechanisms from mod/ (kBK.mod, kBK_nml.mod, pas_nml2.mod, etc.)"
  rm -rf x86_64 || true
  nrnivmodl mod

  echo "[IT2 kBK native vs kBK_nml 2/4] Running native kBK full-geometry test (dt=0.025 ms)"
  python3 run_neuron_kBK_native.py

  echo "[IT2 kBK native vs kBK_nml 3/4] Running kBK_nml full-geometry test (dt=0.025 ms)"
  python3 run_neuron_kBK_nml.py

  echo "[IT2 kBK native vs kBK_nml 4/4] Comparing traces (step-aligned in ms)"
  python3 compare/compare_kBK_native_vs_nml.py

  echo "[IT2 kBK native vs kBK_nml] Done. See compare/kBK_native_vs_nml for outputs."
}

run_kap_native_vs_nml() {
  echo "[IT2 kap native vs kap_nml 1/4] Compile mechanisms from mod/ (kap_BS.mod, kap_nml.mod, pas_nml2.mod, etc.)"
  rm -rf x86_64 || true
  nrnivmodl mod

  echo "[IT2 kap native vs kap_nml 2/4] Running native kap full-geometry test (dt=0.025 ms)"
  python3 run_neuron_kap_native.py

  echo "[IT2 kap native vs kap_nml 3/4] Running kap_nml full-geometry test (dt=0.025 ms)"
  python3 run_neuron_kap_nml.py

  echo "[IT2 kap native vs kap_nml 4/4] Comparing traces (step-aligned in ms)"
  python3 compare/compare_kap_native_vs_nml.py

  echo "[IT2 kap native vs kap_nml] Done. See compare/kap_native_vs_nml for outputs."
}

run_native_vs_netpyne() {
  echo "[IT2 native vs NetPyNE 1/4] Compile mechanisms from mod/ (IT2.mod, h_kole.mod, cadad.mod, cal_mig.mod, can_mig.mod, cat_mig.mod, kBK.mod, kap_BS.mod, kdr_BS.mod, nax_BS.mod, etc.)"
  rm -rf x86_64 || true
  nrnivmodl mod

  echo "[IT2 native vs NetPyNE 2/4] Running pure NEURON IT2_reduced cell (dt=0.025 ms, tstop=700 ms)"
  python3 run_neuron_IT2_native.py

  echo "[IT2 native vs NetPyNE 3/4] Running NetPyNE IT2_reduced cell (dt=0.025 ms, tstop=700 ms)"
  python3 IT2_netpy.py

  echo "[IT2 native vs NetPyNE 4/4] Comparing traces (step-aligned in ms)"
  python3 compare/compare_IT2_native_vs_netpyne.py

  echo "[IT2 native vs NetPyNE] Done. See compare/it2_native_vs_netpyne for outputs."
}

run_nml_vs_netpyne() {
  echo "[IT2 NML-fix vs NetPyNE 1/4] Compile mechanisms from mod/ (ih_nml.mod, cal_nml.mod, can_nml.mod, cat_nml.mod, kBK_nml.mod, kap_nml.mod, kdr_nml.mod, kdr_soma_nml.mod, nax_nml.mod, cadad_IT2_*.mod, pas/mod, etc.)"
  rm -rf x86_64 || true
  nrnivmodl mod

  echo "[IT2 NML-fix vs NetPyNE 2/4] Running NEURON IT2_reduced cell with NML-fix mechanisms (dt=0.025 ms, tstop=700 ms)"
  python3 run_neuron_IT2_nml.py

  echo "[IT2 NML-fix vs NetPyNE 3/4] Running NetPyNE IT2_reduced cell (dt=0.025 ms, tstop=700 ms)"
  python3 IT2_netpy.py

  echo "[IT2 NML-fix vs NetPyNE 4/4] Comparing traces (step-aligned in ms)"
  python3 compare/compare_IT2_nml_vs_netpyne.py

  echo "[IT2 NML-fix vs NetPyNE] Done. See compare/it2_nml_vs_netpyne for outputs."
}

run_nax_native_vs_nml() {
  echo "[IT2 nax native vs nax_nml 1/4] Compile mechanisms from mod/ (nax_BS.mod, nax_nml.mod, pas_nml2.mod, etc.)"
  rm -rf x86_64 || true
  nrnivmodl mod

  echo "[IT2 nax native vs nax_nml 2/4] Running native nax single-channel test (dt=0.025 ms)"
  python3 run_neuron_nax_native.py

  echo "[IT2 nax native vs nax_nml 3/4] Running nax_nml single-channel test (dt=0.025 ms)"
  python3 run_neuron_nax_nml.py

  echo "[IT2 nax native vs nax_nml 4/4] Comparing traces (step-aligned in ms)"
  python3 compare/compare_nax_native_vs_nml.py

  echo "[IT2 nax native vs nax_nml] Done. See compare/nax_native_vs_nml for outputs."
}

run_cal_native_vs_nml() {
  echo "[IT2 cal native vs cal_nml 1/4] Compile mechanisms from mod/ (cal_mig.mod, cal_nml.mod, pas_nml2.mod, etc.)"
  rm -rf x86_64 || true
  nrnivmodl mod

  echo "[IT2 cal native vs cal_nml 2/4] Running native cal full-geometry test (dt=0.025 ms)"
  python3 run_neuron_cal_native.py

  echo "[IT2 cal native vs cal_nml 3/4] Running cal_nml full-geometry test (dt=0.025 ms)"
  python3 run_neuron_cal_nml.py

  echo "[IT2 cal native vs cal_nml 4/4] Comparing traces (step-aligned in ms)"
  python3 compare/compare_cal_native_vs_nml.py

  echo "[IT2 cal native vs cal_nml] Done. See compare/cal_native_vs_nml for outputs."
}

run_can_native_vs_nml() {
  echo "[IT2 can native vs can_nml 1/4] Compile mechanisms from mod/ (can_mig.mod, can_nml.mod, pas_nml2.mod, etc.)"
  rm -rf x86_64 || true
  nrnivmodl mod

  echo "[IT2 can native vs can_nml 2/4] Running native can full-geometry test (dt=0.025 ms)"
  python3 run_neuron_can_native.py

  echo "[IT2 can native vs can_nml 3/4] Running can_nml full-geometry test (dt=0.025 ms)"
  python3 run_neuron_can_nml.py

  echo "[IT2 can native vs can_nml 4/4] Comparing traces (step-aligned in ms)"
  python3 compare/compare_can_native_vs_nml.py

  echo "[IT2 can native vs can_nml] Done. See compare/can_native_vs_nml for outputs."
}

run_cat_native_vs_nml() {
  echo "[IT2 cat native vs cat_nml 1/4] Compile mechanisms from mod/ (cat_mig.mod, cat_nml.mod, pas_nml2.mod, etc.)"
  rm -rf x86_64 || true
  nrnivmodl mod

  echo "[IT2 cat native vs cat_nml 2/4] Running native cat full-geometry test (dt=0.025 ms)"
  python3 run_neuron_cat_native.py

  echo "[IT2 cat native vs cat_nml 3/4] Running cat_nml full-geometry test (dt=0.025 ms)"
  python3 run_neuron_cat_nml.py

  echo "[IT2 cat native vs cat_nml 4/4] Comparing traces (step-aligned in ms)"
  python3 compare/compare_cat_native_vs_nml.py

  echo "[IT2 cat native vs cat_nml] Done. See compare/cat_native_vs_nml for outputs."
}

run_all() {
  echo "[IT2 all] Running all single-channel and full-cell comparisons..."

  # Single-channel comparisons (native vs NML)
  run_ih_native_vs_nml
  run_nax_native_vs_nml
  run_kap_native_vs_nml
  run_kdr_native_vs_nml
  run_kBK_native_vs_nml
  run_cal_native_vs_nml
  run_can_native_vs_nml
  run_cat_native_vs_nml

  # Full-cell comparisons
  run_native_vs_netpyne
  run_nml_vs_netpyne

  echo "[IT2 all] Completed all IT2 comparison workflows."
}

main() {
  case "${1-}" in
    --all)
      run_all
      ;;
    --native-vs-netpyne)
      run_native_vs_netpyne
      ;;
    --nml-vs-netpyne|--nml-fix-vs-netpyne)
      run_nml_vs_netpyne
      ;;
    --kdr-native-vs-nml)
      run_kdr_native_vs_nml
      ;;
    --kBK-native-vs-nml)
      run_kBK_native_vs_nml
      ;;
    --ih-native-vs-nml)
      run_ih_native_vs_nml
      ;;
    --kap-native-vs-nml)
      run_kap_native_vs_nml
      ;;
    --nax-native-vs-nml)
      run_nax_native_vs_nml
      ;;
    --cal-native-vs-nml)
      run_cal_native_vs_nml
      ;;
    --can-native-vs-nml)
      run_can_native_vs_nml
      ;;
    --cat-native-vs-nml)
      run_cat_native_vs_nml
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
