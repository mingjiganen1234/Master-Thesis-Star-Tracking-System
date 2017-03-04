// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2014.4
// Copyright (C) 2014 Xilinx Inc. All rights reserved.
// 
// ===========================================================

#ifndef _CCLabel_preProcess_HH_
#define _CCLabel_preProcess_HH_

#include "systemc.h"
#include "AESL_pkg.h"


namespace ap_rtl {

struct CCLabel_preProcess : public sc_module {
    // Port declarations 15
    sc_in_clk ap_clk;
    sc_in< sc_logic > ap_rst;
    sc_in< sc_logic > ap_start;
    sc_out< sc_logic > ap_done;
    sc_out< sc_logic > ap_idle;
    sc_out< sc_logic > ap_ready;
    sc_out< sc_lv<32> > Image_r_Addr_A;
    sc_out< sc_logic > Image_r_EN_A;
    sc_out< sc_lv<4> > Image_r_WEN_A;
    sc_out< sc_lv<32> > Image_r_Din_A;
    sc_in< sc_lv<32> > Image_r_Dout_A;
    sc_out< sc_lv<6> > lbImage_address0;
    sc_out< sc_logic > lbImage_ce0;
    sc_out< sc_logic > lbImage_we0;
    sc_out< sc_lv<32> > lbImage_d0;


    // Module declarations
    CCLabel_preProcess(sc_module_name name);
    SC_HAS_PROCESS(CCLabel_preProcess);

    ~CCLabel_preProcess();

    sc_trace_file* mVcdFile;

    sc_signal< sc_lv<4> > ap_CS_fsm;
    sc_signal< sc_logic > ap_sig_cseq_ST_st1_fsm_0;
    sc_signal< bool > ap_sig_bdd_22;
    sc_signal< sc_lv<4> > i_1_fu_87_p2;
    sc_signal< sc_lv<4> > i_1_reg_149;
    sc_signal< sc_logic > ap_sig_cseq_ST_st2_fsm_1;
    sc_signal< bool > ap_sig_bdd_49;
    sc_signal< sc_lv<6> > tmp_fu_97_p3;
    sc_signal< sc_lv<6> > tmp_reg_154;
    sc_signal< sc_lv<1> > exitcond1_fu_81_p2;
    sc_signal< sc_lv<4> > j_1_fu_115_p2;
    sc_signal< sc_lv<4> > j_1_reg_162;
    sc_signal< sc_logic > ap_sig_cseq_ST_st3_fsm_2;
    sc_signal< bool > ap_sig_bdd_64;
    sc_signal< sc_lv<64> > tmp_3_fu_126_p1;
    sc_signal< sc_lv<64> > tmp_3_reg_167;
    sc_signal< sc_lv<1> > exitcond_fu_109_p2;
    sc_signal< sc_lv<4> > i_reg_58;
    sc_signal< sc_lv<4> > j_reg_69;
    sc_signal< sc_logic > ap_sig_cseq_ST_st4_fsm_3;
    sc_signal< bool > ap_sig_bdd_88;
    sc_signal< sc_lv<32> > Image_r_Addr_A_orig;
    sc_signal< sc_lv<3> > tmp_31_fu_93_p1;
    sc_signal< sc_lv<6> > j_cast1_fu_105_p1;
    sc_signal< sc_lv<6> > tmp_2_fu_121_p2;
    sc_signal< sc_lv<1> > tmp_4_fu_131_p2;
    sc_signal< sc_lv<4> > ap_NS_fsm;
    static const sc_logic ap_const_logic_1;
    static const sc_logic ap_const_logic_0;
    static const sc_lv<4> ap_ST_st1_fsm_0;
    static const sc_lv<4> ap_ST_st2_fsm_1;
    static const sc_lv<4> ap_ST_st3_fsm_2;
    static const sc_lv<4> ap_ST_st4_fsm_3;
    static const sc_lv<32> ap_const_lv32_0;
    static const sc_lv<1> ap_const_lv1_1;
    static const sc_lv<32> ap_const_lv32_1;
    static const sc_lv<1> ap_const_lv1_0;
    static const sc_lv<32> ap_const_lv32_2;
    static const sc_lv<4> ap_const_lv4_0;
    static const sc_lv<32> ap_const_lv32_3;
    static const sc_lv<4> ap_const_lv4_8;
    static const sc_lv<4> ap_const_lv4_1;
    static const sc_lv<3> ap_const_lv3_0;
    static const sc_lv<32> ap_const_lv32_46;
    // Thread declarations
    void thread_ap_clk_no_reset_();
    void thread_Image_r_Addr_A();
    void thread_Image_r_Addr_A_orig();
    void thread_Image_r_Din_A();
    void thread_Image_r_EN_A();
    void thread_Image_r_WEN_A();
    void thread_ap_done();
    void thread_ap_idle();
    void thread_ap_ready();
    void thread_ap_sig_bdd_22();
    void thread_ap_sig_bdd_49();
    void thread_ap_sig_bdd_64();
    void thread_ap_sig_bdd_88();
    void thread_ap_sig_cseq_ST_st1_fsm_0();
    void thread_ap_sig_cseq_ST_st2_fsm_1();
    void thread_ap_sig_cseq_ST_st3_fsm_2();
    void thread_ap_sig_cseq_ST_st4_fsm_3();
    void thread_exitcond1_fu_81_p2();
    void thread_exitcond_fu_109_p2();
    void thread_i_1_fu_87_p2();
    void thread_j_1_fu_115_p2();
    void thread_j_cast1_fu_105_p1();
    void thread_lbImage_address0();
    void thread_lbImage_ce0();
    void thread_lbImage_d0();
    void thread_lbImage_we0();
    void thread_tmp_2_fu_121_p2();
    void thread_tmp_31_fu_93_p1();
    void thread_tmp_3_fu_126_p1();
    void thread_tmp_4_fu_131_p2();
    void thread_tmp_fu_97_p3();
    void thread_ap_NS_fsm();
};

}

using namespace ap_rtl;

#endif
