#include <TurbulentSimulation.h>

TurbulentSimulation::TurbulentSimulation(Parameters &parameters, TurbulentFlowField &flowField):
	Simulation(parameters, flowField),
	_flowField(flowField)
{
}

// TODO: Changes for turbulent simulation not implemented yet!
void TurbulentSimulation::solveTimestep(){
	std::cout << "Solving timestep for turbulent flow" << std::endl;
	_flowField.getTurbulentViscosity();
	// determine and set max. timestep which is allowed in this simulation
	setTimeStep();
	// compute fgh
	_fghIterator.iterate();
	// set global boundary values
	_wallFGHIterator.iterate();
	// compute the right hand side
	_rhsIterator.iterate();
	// solve for pressure 
	_solver.solve();
	// TODO WS2: communicate pressure values
	_parallelManager.communicatePressure();
	// compute velocity
	_velocityIterator.iterate();
	// set obstacle boundaries
	_obstacleIterator.iterate();
	// TODO WS2: communicate velocity values
	_parallelManager.communicateVelocity();
	// Iterate for velocities on the boundary
	_wallVelocityIterator.iterate();
}

// TODO: Changes for turbulent simulation not implemented yet!
void TurbulentSimulation::setTimeStep(){

	FLOAT localMin, globalMin;
	assertion(_parameters.geometry.dim == 2 || _parameters.geometry.dim == 3);
	FLOAT factor = 1.0/(_parameters.meshsize->getDxMin() * _parameters.meshsize->getDxMin()) +
		         1.0/(_parameters.meshsize->getDyMin() * _parameters.meshsize->getDyMin());

	// determine maximum velocity
	_maxUStencil.reset();
	_maxUFieldIterator.iterate();
	_maxUBoundaryIterator.iterate();
	if (_parameters.geometry.dim == 3) {
	factor += 1.0/(_parameters.meshsize->getDzMin() * _parameters.meshsize->getDzMin());
	_parameters.timestep.dt = 1.0 / _maxUStencil.getMaxValues()[2];
	} else {
	_parameters.timestep.dt = 1.0 / _maxUStencil.getMaxValues()[0];
	}

	localMin = std::min(_parameters.timestep.dt,
		                            std::min(std::min(_parameters.flow.Re/(2*factor),
		                            1.0 / _maxUStencil.getMaxValues()[0]),
		                            1.0 / _maxUStencil.getMaxValues()[1]));

	// Here, we select the type of operation before compiling. This allows to use the correct
	// data type for MPI. Not a concern for small simulations, but useful if using heterogeneous
	// machines.

	globalMin = MY_FLOAT_MAX;
	MPI_Allreduce(&localMin, &globalMin, 1, MY_MPI_FLOAT, MPI_MIN, PETSC_COMM_WORLD);

	_parameters.timestep.dt = globalMin;
	_parameters.timestep.dt *= _parameters.timestep.tau;
	
}

