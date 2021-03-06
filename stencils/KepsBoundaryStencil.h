#ifndef _KE_BOUNDARY_STENCIL_H_
#define _KE_BOUNDARY_STENCIL_H_

#include "../Stencil.h"
#include "../Parameters.h"
#include "../TurbulentFlowField.h"


class KepsBoundaryStencil: public BoundaryStencil<TurbulentFlowField> {

	protected:
		const Parameters & _parameters;

    public:

        /** Constructor
         *
         * @param parameters Parameters of the problem
         */
        KepsBoundaryStencil ( const Parameters & parameters );

        //@brief Functions for the 2D problem. Coordinates entered in alphabetical order.
        //@{
        void applyLeftWall   ( TurbulentFlowField & TurbulentFlowField, int i, int j );
        void applyRightWall  ( TurbulentFlowField & TurbulentFlowField, int i, int j );
        void applyBottomWall ( TurbulentFlowField & TurbulentFlowField, int i, int j );
        void applyTopWall    ( TurbulentFlowField & TurbulentFlowField, int i, int j );
        //@}

        //@brief Functions for the 3D problem. Coordinates entered in alphabetical order.
        //@{
        void applyLeftWall   ( TurbulentFlowField & TurbulentFlowField, int i, int j, int k );
        void applyRightWall  ( TurbulentFlowField & TurbulentFlowField, int i, int j, int k );
        void applyBottomWall ( TurbulentFlowField & TurbulentFlowField, int i, int j, int k );
        void applyTopWall    ( TurbulentFlowField & TurbulentFlowField, int i, int j, int k );
        void applyFrontWall  ( TurbulentFlowField & TurbulentFlowField, int i, int j, int k );
        void applyBackWall   ( TurbulentFlowField & TurbulentFlowField, int i, int j, int k );
        //@}

};

#endif
