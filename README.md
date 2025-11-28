# hifiasm-raw-gfa

**hifiasm-raw-gfa** is an independent, modified version of [hifiasm](https://github.com/chhylp123/hifiasm). Its main purpose is to leverage hifiasm’s powerful error correction and overlap algorithms to quickly generate the raw overlap graph (in GFA format) and exit immediately after the graph is produced, without performing subsequent assembly, cleaning, phasing, or scaffolding.

This tool is ideal for researchers and developers who need to analyze raw assembly graph structure, debug overlap algorithms, or feed the Raw Unitig Graph into custom downstream pipelines.

## Features

* **Core algorithms preserved**: retains hifiasm’s efficient k-mer counting, read correction, and overlap detection.
* **Fast output**: executes only up to the Raw Unitig Graph stage, significantly reducing runtime.
* **GFA export**: directly outputs a standard GFA file, convenient for visualization with tools like Bandage.
* **Lightweight**: removes downstream logic related to Hi-C, Trio binning, and final contig generation.

## Build & Install

This project depends on `zlib`. Please ensure the zlib development library is installed on your system.

Build in the project root using the provided `Makefile`:

```bash
# Build the project
make

# Clean build artifacts if needed
make clean
```

Upon success, the executable `hifiasm-raw` will be generated in the current directory.

## Usage

Basic usage is similar to hifiasm.

```bash
./hifiasm-raw -o <output_prefix> -t <threads> --prt-raw --write-paf <input_reads.fq>
```

## Command Reference

- `-o <prefix>`: Output prefix for generated files (e.g., `<prefix>.bp.raw.r_utg.gfa`).
- `-t <threads>`: Number of CPU threads to use; increase for performance.
- `--prt-raw`: Emit the raw unitig graph; required for this fork’s primary output.
- `--write-paf`: Write pairwise overlaps in PAF format to `<prefix>.ovlp.paf`.
- `<input_reads.fq|fa[.gz]>`: HiFi reads in FASTQ/FASTA; gzip-compressed files supported.

Examples:

```bash
# Minimal raw graph
./hifiasm-raw -o run1 -t 8 --prt-raw reads.fq.gz

# Raw graph + PAF overlaps
./hifiasm-raw -o run2 -t 16 --prt-raw --write-paf reads.fa
```

## Outputs

After completion, the program produces the following key files:

1. **GFA graph file**
   * `<prefix>.bp.raw.r_utg.gfa`: the core output, containing the Raw Unitig Graph with all overlaps and sequence information preserved.

2. **Overlap information** (requires `--write-paf`)
   * `<prefix>.ovlp.paf`: standard PAF file listing pairwise overlaps among reads.

3. **Intermediate binaries**
   * `<prefix>.ec.bin`: error-corrected reads.
   * `<prefix>.ovlp.source.bin` / `<prefix>.ovlp.reverse.bin`: binary index files of sequence overlaps.

Note: The program is designed to exit right after generating the Raw Unitig Graph, so it will not produce hifiasm’s final assembly outputs (e.g., `.p_ctg.gfa` or `.r_utg.gfa`).

## Differences from Upstream hifiasm

1. **Execution truncated**:
   In `Overlaps.cpp`, the graph generation logic is modified. The upstream hifiasm proceeds with graph cleaning, transitive reduction, and haplotype resolution. This project calls `exit(1)` immediately after exporting the Raw Unitig Graph via `ma_ug_print`.

2. **Feature simplification**:
   While most CLI argument parsing is retained, many parameters controlling downstream assembly stages (e.g., Hi-C integration, Trio binning) have no practical effect because the program exits early.


## Quick Start

Use the following minimal steps to generate a raw unitig graph from HiFi reads (FASTQ or FASTA). Replace placeholders with your own paths.

```bash
# 1) Build
make

# 2) Run with common options
./hifiasm-raw \
   -o demo \
   -t 8 \
   --prt-raw \
   --write-paf \
   demo_reads.fq

# Outputs of interest
ls -lh demo.*
# demo.bp.raw.r_utg.gfa      (raw unitig graph)
# demo.ovlp.paf              (pairwise overlaps if --write-paf is set)
# demo.ec.bin, demo.ovlp.*.bin (intermediate binaries)

# 3) Visualize the GFA (example with Bandage)
Bandage GUI
# Or using Bandage command-line:
Bandage image demo.bp.raw.r_utg.gfa demo.png
```

Notes:
* Input can be gzip-compressed reads; ensure your system `zlib` is available.
* Threads (`-t`) should match available CPU cores for best speed.
* The program exits right after emitting the raw graph, by design.

## FAQ

* **What input formats are supported?**: HiFi reads in FASTQ or FASTA. Gzip-compressed files are supported via `zlib`.
* **Why does the program exit with code `1`?**: The upstream flow is intentionally truncated (via `exit(1)` after `ma_ug_print`). This is expected behavior; outputs are written before exit.
* **How do I visualize the GFA?**: Use Bandage (GUI or CLI). The file `<prefix>.bp.raw.r_utg.gfa` is standard GFA and should load directly.
* **Does it perform polishing, phasing, or scaffolding?**: No. Those stages are removed; only raw unitig graph generation is performed.
* **Performance tips**: Increase `-t` to use more cores; ensure fast storage for large PAF/GFA writes; avoid I/O bottlenecks by running on local disks.
* **Can I still get PAF overlaps?**: Yes—pass `--write-paf` to emit `<prefix>.ovlp.paf` alongside the GFA.

## Example Dataset

Below is a small public HiFi dataset you can use for a quick run. If the link changes, any PacBio HiFi FASTQ/FASTA will work.

```bash
# Download a tiny HiFi example (E. coli demo)
# Source: PacBio GitHub/CSIRO demo mirrors are common; update as needed.
curl -L -o ecoli.hifi.demoreads.fq.gz \
   https://raw.githubusercontent.com/pacificbiosciences/datasets/master/misc/ecoli.hifi.demoreads.fq.gz

# Verify integrity
md5sum ecoli.hifi.demoreads.fq.gz
# Expected (example): 1234567890abcdef1234567890abcdef  ecoli.hifi.demoreads.fq.gz

# Check gzip
gzip -t ecoli.hifi.demoreads.fq.gz && echo "gzip OK"

# Optional: quick stats (requires seqkit)
seqkit stats ecoli.hifi.demoreads.fq.gz

# Run
./hifiasm-raw -o ecoli -t 4 --prt-raw --write-paf ecoli.hifi.demoreads.fq.gz

# Inspect outputs
ls -lh ecoli.*
Bandage image ecoli.bp.raw.r_utg.gfa ecoli.png
```

Notes:
- If `seqkit` is not installed, you can skip the stats step or install via your package manager.
- For larger datasets, increase `-t` and ensure sufficient disk space for PAF/GFA.

## Troubleshooting

- **Build fails: missing zlib headers**: Install zlib development package (e.g., `sudo apt-get install zlib1g-dev` on Debian/Ubuntu, `sudo dnf install zlib-devel` on Fedora/RHEL).
- **Compiler errors (C++ features not found)**: Use a modern compiler (GCC ≥ 9 or Clang ≥ 10). Check with `gcc --version`.
- **Exit code is 1**: This is expected; the workflow intentionally calls `exit(1)` after writing raw outputs. Verify files exist before the exit.
- **High memory usage / OOM**: Reduce threads (`-t`), split input files, or run on a machine with more RAM; ensure no competing processes.
- **Bandage cannot open GFA**: Confirm the file path and completeness; re-run ensuring the command finished writing. Update Bandage to the latest version.
- **Slow I/O or large PAF**: Use fast local storage (NVMe/SSD); avoid network filesystems for heavy overlap output; consider disabling `--write-paf` if not needed.

## License & Acknowledgements

This project is adapted from [hifiasm](https://github.com/chhylp123/hifiasm).

* **Original authors**: Haoyu Cheng, Heng Li, et al.
* **License**: MIT License (following the upstream project).

Please cite the original hifiasm papers when using this tool:
> Cheng, H., Concepcion, G.T., Feng, X., Zhang, H., Li H. (2021)
> Haplotype-resolved de novo assembly using phased assembly graphs with
> hifiasm. *Nat Methods*, **18**:170–175.
> https://doi.org/10.1038/s41592-020-01056-5

> Cheng, H., Jarvis, E.D., Fedrigo, O., Koepfli, K.P., Urban, L., Gemmell, N.J., Li, H. (2022)
> Haplotype-resolved assembly of diploid genomes without parental data.
> *Nature Biotechnology*, **40**:1332–1335.
> https://doi.org/10.1038/s41587-022-01261-x

> Cheng, H., Asri, M., Lucas, J., Koren, S., Li, H. (2024)
> Scalable telomere-to-telomere assembly for diploid and polyploid genomes with double graph.
> *Nat Methods*, **21**:967–970.
> https://doi.org/10.1038/s41592-024-02269-8