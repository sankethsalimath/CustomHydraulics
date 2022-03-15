#ifndef HYDRAULICOPENCENTERVALVE_HPP_INCLUDED
#define HYDRAULICOPENCENTERVALVE_HPP_INCLUDED

#include "ComponentEssentials.h"
#include "ComponentUtilities.h"

namespace hopsan {

    //!
    //! @brief Hydraulic Open Center valve of Q-type.
    //! @ingroup HydraulicComponents
    //!
    class HydraulicOpenCenterValve : public ComponentQ
    {
    private:
        // Member variables
        SecondOrderTransferFunction mSpoolPosTF;
        TurbulentFlowFunction qTurb_pa;
        TurbulentFlowFunction qTurb_pb;
        TurbulentFlowFunction qTurb_at;
        TurbulentFlowFunction qTurb_bt;
        TurbulentFlowFunction qTurb_cc;

        // Port and node data pointers
        Port *mpPP, *mpPC1, *mpPT, *mpPA, *mpPC2, *mpPB;
        double *mpPP_p, *mpPP_q, *mpPP_c, *mpPP_Zc, *mpPT_p, *mpPT_q, *mpPT_c, *mpPT_Zc, *mpPA_p, *mpPA_q, *mpPA_c, *mpPA_Zc, *mpPB_p, *mpPB_q, *mpPB_c, *mpPB_Zc, *mpPC1_p, *mpPC1_q, *mpPC1_c, *mpPC1_Zc, *mpPC2_p, *mpPC2_q, *mpPC2_c, *mpPC2_Zc;
        double *mpXvIn, *mpXv, *mpCq, *mpD, *mpF_pa, *mpF_pb, *mpF_at, *mpF_bt, *mpF_cc, *mpXvmax, *mpRho, *mpX_pa, *mpX_pb, *mpX_at, *mpX_bt, *mpX_cc;

        // Constants
        double mOmegah, mDeltah;

    public:
        static Component *Creator()
        {
            return new HydraulicOpenCenterValve();
        }

        void configure()
        {
            mpPP = addPowerPort("PP", "NodeHydraulics");
            mpPL = addPowerPort("PL", "NodeHydraulics");
            mpPT = addPowerPort("PT", "NodeHydraulics");
            mpPA = addPowerPort("PA", "NodeHydraulics");
            mpPB = addPowerPort("PB", "NodeHydraulics");
            mpPC = addPowerPort("PC", "NodeHydraulics");
            mpPD = addPowerPort("PD", "NodeHydraulics");

            addOutputVariable("xv", "Spool position", "m", 0.0, &mpXv);
            addInputVariable("in", "Desired spool position", 0.0, &mpXvIn);

            addInputVariable("C_q", "Flow Coefficient", "-", 0.67, &mpCq);
            addInputVariable("rho", "Oil density", "kg/m^3", 870, &mpRho);
            addInputVariable("d", "Spool Diameter", "m", 0.01, &mpD);
            addInputVariable("f_pa", "Fraction of spool circumference that is opening P-A", "-", 1.0, &mpF_pa);
            addInputVariable("f_pb", "Fraction of spool circumference that is opening P-B", "-", 1.0, &mpF_pb);
            addInputVariable("f_lc", "Fraction of spool circumference that is opening L-C", "-", 1.0, &mpF_lc);
            addInputVariable("f_ld", "Fraction of spool circumference that is opening L-D", "-", 1.0, &mpF_ld);
            addInputVariable("f_tc", "Fraction of spool circumference that is opening T-C", "-", 1.0, &mpF_tc);
            addInputVariable("f_td", "Fraction of spool circumference that is opening T-D", "-", 1.0, &mpF_td);
            addInputVariable("x_pa", "Spool Overlap From Port P To A", "m", -1e-6, &mpX_pa);
            addInputVariable("x_pb", "Spool Overlap From Port P To B", "m", -1e-6, &mpX_pb);
            addInputVariable("x_lc", "Spool Overlap From Port L To C", "m", -1e-6, &mpX_lc);
            addInputVariable("x_ld", "Spool Overlap From Port L To D", "m", -1e-6, &mpX_ld);
            addInputVariable("x_tc", "Spool Overlap From Port C1 To C2", "m", -1e-6, &mpX_tc);
            addInputVariable("x_td", "Spool Overlap From Port L To D", "m", -1e-6, &mpX_td);
            addInputVariable("x_vmax", "Maximum Spool Displacement", "m", 0.01, &mpXvmax);

            addConstant("omega_h", "Resonance Frequency", "Frequency", 100.0, mOmegah);
            addConstant("delta_h", "Damping Factor", "-", 1.0, mDeltah);
        }

        void initialize()
        {
            mpPP_p = getSafeNodeDataPtr(mpPP, NodeHydraulic::Pressure)
            mpPP_q = getSafeNodeDataPtr(mpPP, NodeHydraulic::Flow);
            mpPP_c = getSafeNodeDataPtr(mpPP, NodeHydraulic::WaveVariable);
            mpPP_Zc = getSafeNodeDataPtr(mpPP, NodeHydraulic::CharImpedance);

            mpPT_p = getSafeNodeDataPtr(mpPT, NodeHydraulic::Pressure)
            mpPT_q = getSafeNodeDataPtr(mpPT, NodeHydraulic::Flow);
            mpPT_c = getSafeNodeDataPtr(mpPT, NodeHydraulic::WaveVariable);
            mpPT_Zc = getSafeNodeDataPtr(mpPT, NodeHydraulic::CharImpedance);

            mpPL_p = getSafeNodeDataPtr(mpPL, NodeHydraulic::Pressure)
            mpPL_q = getSafeNodeDataPtr(mpPL, NodeHydraulic::Flow);
            mpPL_c = getSafeNodeDataPtr(mpPL, NodeHydraulic::WaveVariable);
            mpPL_Zc = getSafeNodeDataPtr(mpPL, NodeHydraulic::CharImpedance);

            mpPA_p = getSafeNodeDataPtr(mpPA, NodeHydraulic::Pressure)
            mpPA_q = getSafeNodeDataPtr(mpPA, NodeHydraulic::Flow);
            mpPA_c = getSafeNodeDataPtr(mpPA, NodeHydraulic::WaveVariable);
            mpPA_Zc = getSafeNodeDataPtr(mpPa, NodeHydraulic::CharImpedance);

            mpPB_p = getSafeNodeDataPtr(mpPB, NodeHydraulic::Pressure)
            mpPB_q = getSafeNodeDataPtr(mpPB, NodeHydraulic::Flow);
            mpPB_c = getSafeNodeDataPtr(mpPB, NodeHydraulic::WaveVariable);
            mpPB_Zc = getSafeNodeDataPtr(mpPB, NodeHydraulic::CharImpedance);

            mpPC_p = getSafeNodeDataPtr(mpPC, NodeHydraulic::Pressure)
            mpPC_q = getSafeNodeDataPtr(mpPC, NodeHydraulic::Flow);
            mpPC_c = getSafeNodeDataPtr(mpPC, NodeHydraulic::WaveVariable);
            mpPC_Zc = getSafeNodeDataPtr(mpPC, NodeHydraulic::CharImpedance);

            mpPD_p = getSafeNodeDataPtr(mpPD, NodeHydraulic::Pressure)
            mpPD_q = getSafeNodeDataPtr(mpPD, NodeHydraulic::Flow);
            mpPD_c = getSafeNodeDataPtr(mpPD, NodeHydraulic::WaveVariable);
            mpPD_Zc = getSafeNodeDataPtr(mpPD, NodeHydraulic::CharImpedance);

            double num[3] = {1.0, 0.0, 0.0};
            double den[3] = {1.0, 2.0*mDeltah/mOmegah, 1.0/(mOmegah*Omegah)}
            double initXv = limit((*mpXv), -(*mpXvmax), (*mpXvmax));
            mSpoolPosTF.initialize(mTimestep, num, den, initXv, initXv, -(*mpXvmax), (*mpXvmax))
        }

        void simulateOneTimestep()
        {
            //Declare local variables
            double xv, xpanom, xpbnom, xlcnom, xldnom, xxtcnom, xtdnom, Kcpa, Kcpb, Kclc, Kcld, Kctc, Kctd, qpa, qpb, qlc, qld, qtc, qtd;
            double pp, qp, cp, Zcp, pt, qt, ct, Zct, pl, ql, cl, Zcl, xvin, pa, qa, ca, Zca, pb, qb, cb, Zcb, pc, qc, cc, Zcc, pd, qd, cd, Zcd;
            double Cq, rho, xvmax, d, f_pa, f_pb, f_lc, f_ld, f_tc, f_td, x_pa, x_pb, x_lc, x_ld, x_tc, x_td;
            bool cav = false;

            //Get variable values from nodes
            cp = (*mpPP_c);
            Zcp = (*mpPP_Zc);
            ct = (*mpPT_c);
            Zct = (*mpPT_Zc);
            cl = (*mpPL_c);
            Zcl = (*mpPL_Zc);
            ca = (*mpPA_c);
            Zca = (*mpPA_Zc);
            cb = (*mpPB_c);
            Zcb = (*mpPB_Zc);
            cc = (*mpPC_c);
            Zcc = (*mpPC_Zc);
            cd = (*mpPD_c);
            Zcd = (*mpPD_Zc);

            xvin = (*mpXvIn);
            Cq = (*mpCq);
            rho = (*mpRho);
            xvmax = (*mpXvmax);
            d = (*mpD);
            f_pa = (*mpF_pa);
            f_pb = (*mpF_pb);
            f_lc = (*mpF_lc);
            f_ld = (*mpF_ld);
            f_tc = (*mpF_tc);
            f_td = (*mpF_td);

            limitValue(xvin, -xvmax, xvmax);
            mSpoolPosTF.update(xvin);
            xv = mSpoolPosTF.value();

            //Valve equations
            xpanom = std::max(xv-x_pa, 0.0);
            xpbnom = std::max(-xv-x_pb, 0.0);
            
            
        }
