#include "Overlaps.h"
#include "hic.h"
#include "inter.h"
#include "horder.h"
#include "tovlp.h"
#include "htab.h"
#include "Process_Read.h"
#include "rcut.h"
#include "Purge_Dups.h"

// Stubs for Correct.o
uint64_t check_ul_ov_t_consist(ul_ov_t *x, ul_ov_t *y, int64_t ql, int64_t tl, double diff) { return 0; }
uint32_t infer_se(uint32_t qs, uint32_t qe, uint32_t ts, uint32_t te, uint32_t rev, uint32_t rqs, uint32_t rqe, uint32_t *rts, uint32_t *rte) { return 0; }
uint32_t gen_src_shared_interval_simple(uint32_t src, ma_ug_t *ug, uint64_t *flt, uint64_t flt_n, kv_ul_ov_t *res) { return 0; }

// Stubs for Overlaps.o
void get_bubbles(bubble_type* bub, uint64_t id, uint32_t* beg, uint32_t* sink, uint32_t** a, uint32_t* n, uint64_t* pathBase) {}
uint64_t* get_hifi2ul_list(all_ul_t *x, uint64_t hid, uint64_t* a_n) { return NULL; }
void fill_unitig(uint64_t* buffer, uint32_t bufferLen, asg_t* read_g, kvec_asg_arc_t_warp* edge, uint32_t is_l, uint64_t* l) {}
void chain_trans_ovlp(hap_cov_t *cov, utg_trans_t *o, ma_ug_t *ug, asg_t *read_sg, buf_t* xReads, uint32_t targetBaseLen, uint32_t* xEnd) {}
void collect_trans_ovlp(const char* cmd, buf_t* pri, uint64_t pri_offset, buf_t* aux, uint64_t aux_offset, ma_ug_t *ug, utg_trans_t *o) {}
hc_edge* push_hc_edge(hc_linkeage* x, uint64_t uID, double weight, int dir, uint64_t* d) { return NULL; }
void trans_base_infer(ma_ug_t *ug, asg_t *sg, ug_opt_t *uopt, kv_u_trans_t *res, bubble_type *bub) {}
void destory_bubbles(bubble_type* bub) {}
void order_contig_trans(kv_u_trans_t *in) {}
void gen_contig_trans(const ug_opt_t *uopt, asg_t *sg, ma_ug_t *qry, scaf_res_t *qry_sc, ma_ug_t *ref, scaf_res_t *ref_sc, ma_ug_t *gfa, kv_u_trans_t *ta, uint32_t qoff, uint32_t toff, bubble_type *bu, kv_u_trans_t *res) {}
void gen_contig_self(const ug_opt_t *uopt, asg_t *sg, ma_ug_t *db, scaf_res_t *db_sc, ma_ug_t *gfa, kv_u_trans_t *ta, uint64_t soff, bubble_type *bu, kv_u_trans_t *res, uint32_t is_exact) {}
void sort_uc_block_qe(uc_block_t* a, uint64_t a_n) {}
uint32_t test_yak_binning(char* fn, char *cmd) { return 0; }
void ha_triobin(const hifiasm_opt_t *opt) {}
void asg_bub_collect_ovlp(ma_ug_t *ug, uint32_t v0, buf_t *b, utg_trans_t *o) {}
utg_trans_t *init_utg_trans_t(ma_ug_t *ug, ma_hit_t_alloc* reverse_sources, ma_sub_t *coverage_cut, R_to_U* ruIndex, asg_t *read_g, int max_hang, int min_ovlp) { return NULL; }
int asg_arc_decompress_mul(asg_t *g, ma_ug_t *ug, asg_t *read_sg, uint32_t positive_flag, uint32_t negative_flag, ma_hit_t_alloc* reverse_sources, R_to_U* ruIndex, utg_trans_t *o) { return 0; }
void horder_clean_sg_by_utg(asg_t *sg, ma_ug_t *ug) {}
uint32_t *ha_polybin_list(const hifiasm_opt_t *opt) { return NULL; }
void hic_benchmark(ma_ug_t *ug, asg_t* read_g) {}
void trans_base_mmhap_infer(ma_ug_t *ug, asg_t *sg, ug_opt_t *uopt, kv_u_trans_t *res) {}
scaf_res_t *gen_contig_path(const ug_opt_t *uopt, asg_t *sg, ma_ug_t *ctg, ma_ug_t *ref) { return NULL; }
void ha_aware_order(kvec_pe_hit *r_hits, asg_t *rg, ma_ug_t *ug_fa, ma_ug_t *ug_mo, kv_u_trans_t *ref, ug_opt_t *opt, uint32_t round) {}
void identify_bubbles(ma_ug_t* ug, bubble_type* bub, uint8_t *r_het_flag, kv_u_trans_t *ref) {}
uint32_t clean_contain_g(const ug_opt_t *uopt, asg_t *sg, uint32_t push_trans) { return 0; }

// Stubs for rcut.o
void osg_destroy(osg_t *g) {}
void layout_mc_clus_t(const mc_match_t *ma, uint32_t *a, uint32_t an, scg_t *sg, uint32_t *buf, uint64_t *idx, ma_ug_t* ug, double min_cut, double max_cut, uint64_t cut_round) {}
int get_specific_hap_overlap(kvec_hap_overlaps* x, uint32_t qn, uint32_t tn) { return 0; }
void set_reverse_hap_overlap(hap_overlaps* dest, hap_overlaps* source, uint32_t* types) {}

// Stubs for gfa_ut.o
uint64_t ul_refine_alignment(const ug_opt_t *uopt, asg_t *sg) { return 0; }
void identify_bubbles_recal_poy(asg_t* sg, ma_ug_t* ug, bubble_type* bub, uint8_t *r_het_flag, ma_hit_t_alloc* sources, R_to_U* ruIndex, kv_u_trans_t *ref) {}
void filter_ul_ug(ma_ug_t *ug) {}
void gen_ul_vec_rid_t(all_ul_t *x, All_reads *rdb, ma_ug_t *ug) {}
void update_ug_arch_ul_mul(ma_ug_t *ug) {}
uint32_t ugl_cover_check(uint64_t is, uint64_t ie, ma_utg_t *u) { return 0; }
void identify_bubbles_recal(asg_t* sg, ma_ug_t* ug, bubble_type* bub, uint8_t *r_het_flag, ma_hit_t_alloc* sources, R_to_U* ruIndex, kv_u_trans_t *ref) {}

// Stubs for Assembly.o
void ha_extract_print_list(const All_reads *rs, int n_rounds, const char *o) {}

// Stubs for htab.o
int ha_analyze_count(int n_cnt, int start_cnt, int m_peak_hom, const int64_t *cnt, int *peak_het) { return 0; }

// NEW STUBS
void bp_solve(ug_opt_t *opt, kv_u_trans_t *ref, ma_ug_t *ug, asg_t *sg, bubble_type *bub, double cis_rate) {}
int32_t write_all_ul_t(all_ul_t *x, char* file_name, ma_ug_t *ug) { return 0; }
int32_t load_all_ul_t(all_ul_t *x, char* file_name, All_reads *hR, ma_ug_t *ug) { return 0; }
kv_u_trans_t *pt_pdist(ma_ug_t *ug, asg_t *read_g, ma_sub_t *coverage_cut, ma_hit_t_alloc* sources, kvec_asg_arc_t_warp* edge, int max_hang, int min_ovlp, uint32_t min_chain_cnt) { return NULL; }
void purge_dups(ma_ug_t *ug, asg_t *read_g, ma_sub_t* coverage_cut, ma_hit_t_alloc* sources, ma_hit_t_alloc* reverse_sources, R_to_U* ruIndex, kvec_asg_arc_t_warp* edge, float density, uint32_t purege_minLen, int max_hang, int min_ovlp, float drop_ratio, uint32_t just_contain, uint32_t just_coverage, hap_cov_t *cov, uint32_t collect_p_trans, uint32_t collect_p_trans_f) {}
void hic_analysis(ma_ug_t *ug, asg_t* read_g, trans_chain* t_ch, ug_opt_t *opt, mmhap_t **rh, kvec_pe_hit **rhits) {}
void trio_phasing_refine(ma_ug_t *ug, asg_t* sg, kv_u_trans_t *ta, ug_opt_t *opt) {}
void ul_load(const ug_opt_t *uopt) {}
void clear_all_ul_t(all_ul_t *x) {}
ma_ug_t *ul_realignment(const ug_opt_t *uopt, asg_t *sg, uint32_t double_check_cache, const char *bin_file) { return NULL; }
