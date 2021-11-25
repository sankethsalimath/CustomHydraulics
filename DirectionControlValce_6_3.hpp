#ifdef DIRECTIONCONTROLVALVE63_H
#define DIRECTIONCONTROLVALVE63_H

#include "ComponentEssentials.h"
#include "ComponentUtilities.h"

namespace hopsan {

    class DirectionControlValve63 : public ComponentQ
    {
    private:
        // Member variables
        SecondOrderTransferFunction mSpoolPosTF;
        TurbulentFlowFunction mQTurb_pa;
        TurbulentFlowFunction mQTurb_pb;
        TurbulentFlowFunction mQTurb_at;
        TurbulentFlowFunction mQTurb_bt;
        TurbulentFlowFunction mQTurb_la;
        TurbulentFlowFunction mQTurb_lb;

        // Port and node data pointers
        Port *mpPP, *mpPT, *mpPA, *mpPB, *mpPL;
        double  *mpPP_p, *mpPP_q, *mpPP_c, *mpPP_Zc,
                *mpPT_p, *mpPT_q, *mpPT_c, *mpPT_Zc,
                *mpPA_p, *mpPA_q, *mpPA_c, *mpPA_Zc,
                *mpPB_p, *mpPB_q, *mpPB_c, *mpPB_Z6,
                *mpPL_p, *mpPL_q, *mpPL_c, *mpPL_Zc;
        double *mpXvIn, *mpXv;
        double *mpCq, *mpD, *mpF_pa, *mpF_pb, *mpF_at, *mpF_bt, *mpF_la, *mpF_lb, *mpXvmax, *mpRho, *mpX_pa, *mpX_pb, *mpX_at, *mpX_bt, *mpX_la, *mpX_lb;

        //Constants
        double mOmegah, mDeltah;

    public:
        static Component *Creator()
        {
            return new DirectionControlValve63();
        }

        void configure()
        {
            mpPP = addPowerPort("PP", "NodeHydraulic");
            mpPT = addPowerPort("PT", "NodeHydraulic");
            mpPA = addPowerPort("PA", "NodeHydraulic");
            mpPB = addPowerPort("PB", "NodeHydraulic");
            mpPL = addPowerPort("PL", "NodeHydraulic");

            addOutputVariable("xv", "Spool position", "m", 0.0, &mpXv);

            addInputVariable("in", "Desired spool position", "m", 0.0, &mpXvIn);

            addInputVariable("C_q", "Flow Coefficient", "-", 0.67, &mpCq);
            addInputVariable("rho", "Oil density", "kg/m^3", 870, &mpRho);
            addInputVariable("d", "Spool Diameter", "m", 0.01, &mpD);
            addInputVariable("f_pa", "Fraction of spool circumference that is opening P-A", "-", 1.0, &mpF_pa);
            addInputVariable("f_pb", "Fraction of spool circumference that is opening P-B", "-", 1.0, &mpF_pb);
            addInputVariable("f_at", "Fraction of spool circumference that is opening A-T", "-", 1.0, &mpF_at);
            addInputVariable("f_bt", "Fraction of spool circumference that is opening B-T", "-", 1.0, &mpF_bt);
            addInputVariable("x_pa", "Spool Overlap From Port P To A", "m", -1e-6, &mpX_pa);
            addInputVariable("x_pb", "Spool Overlap From Port P To B", "m", -1e-6, &mpX_pb);
            addInputVariable("x_at", "Spool Overlap From Port A To T", "m", -1e-6, &mpX_at);
            addInputVariable("x_bt", "Spool Overlap From Port A To T", "m", -1e-6, &mpX_bt);
            addInputVariable("x_vmax", "Maximum Spool Displacement", "m", 0.01, &mpXvmax);

            addConstant("omega_h", "Resonance Frequency", "Frequency", 100.0, mOmegah);
            addConstant("delta_h", "Damping Factor", "-", 1.0, mDeltah);
        }

        void initialize()
        {
            mpND_p1 = getSafeNodeDataPtr(mpP1, NodeHydraulic::Pressure);
            mpND_q1 = getSafeNodeDataPtr(mpP1, NodeHydraulic::Flow);
            mpND_c1 = getSafeNodeDataPtr(mpP1, NodeHydraulic::WaveVariable);
            mpND_Zc1 = getSafeNodeDataPtr(mpP1, NodeHydraulic::CharImperedence);
        }

        void simulateOneTimestep()
        {
            double p1, q1, c1, Zc1;

            //Get variable values from nodes
            c1 = (*mpND_c1);
            Zc1 = (*mpND_Zc1);
            Kc = (*mpND_Kc);

            //DCV equations

        }
    }
}
