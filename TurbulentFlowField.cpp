#include "TurbulentFlowField.h"

TurbulentFlowField::TurbulentFlowField ( int Nx, int Ny ) :
	FlowField(Nx, Ny),
	_nitau( ScalarField ( Nx + 3, Ny + 3 ) ),
	_distance( ScalarField ( Nx + 3, Ny + 3 ) ),
	_kinetic( ScalarField ( Nx + 3, Ny + 3 ) ),
	_dissip( ScalarField ( Nx + 3, Ny + 3 ) ) ,
	_fmu( ScalarField ( Nx + 3, Ny + 3 ) ){}
	//_centerLineBuffer ( new FLOAT[Nx + 3] )


TurbulentFlowField::TurbulentFlowField ( int Nx, int Ny, int Nz ) :
	FlowField(Nx, Ny, Nz),
	_nitau( ScalarField ( Nx + 3, Ny + 3, Nz+3 ) ),
	_distance( ScalarField ( Nx + 3, Ny + 3, Nz+3 ) ),
	_kinetic( ScalarField ( Nx + 3, Ny + 3, Nz+3 ) ),
	_dissip( ScalarField ( Nx + 3, Ny + 3, Nz+3 ) ) ,  
	_fmu( ScalarField ( Nx + 3, Ny + 3, Nz+3 ) ){}
	//_centerLineBuffer ( new FLOAT[Nx + 3] )


TurbulentFlowField::TurbulentFlowField (const Parameters & parameters):
	FlowField(parameters),
	_nitau(parameters.geometry.dim==2?ScalarField(_size_x + 3, _size_y + 3):
                      ScalarField(_size_x + 3, _size_y + 3, _size_z + 3)),
	_distance(parameters.geometry.dim==2?ScalarField(_size_x + 3, _size_y + 3):
                      ScalarField(_size_x + 3, _size_y + 3, _size_z + 3)),
	_kinetic(parameters.geometry.dim==2?ScalarField(_size_x + 3, _size_y + 3):
                      ScalarField(_size_x + 3, _size_y + 3, _size_z + 3)),
	_dissip(parameters.geometry.dim==2?ScalarField(_size_x + 3, _size_y + 3):
                      ScalarField(_size_x + 3, _size_y + 3, _size_z + 3)), 
	_fmu(parameters.geometry.dim==2?ScalarField(_size_x + 3, _size_y + 3):
                      ScalarField(_size_x + 3, _size_y + 3, _size_z + 3)){}
	//_centerLineBuffer ( new FLOAT[_size_x + 3] )

ScalarField & TurbulentFlowField::getTurbulentViscosity () {
    return _nitau;
}

ScalarField & TurbulentFlowField::getWallDistance () {
    return _distance;
}

ScalarField & TurbulentFlowField::getKineticEnergy () {
    return _kinetic;
}

ScalarField & TurbulentFlowField::getDissipationRate () {
    return _dissip;
}

ScalarField & TurbulentFlowField::getFmu () {
    return _fmu;
}

FLOAT TurbulentFlowField::getWallDistance(int i, int j) {
	return _distance.getScalar(i, j);
}
FLOAT TurbulentFlowField::getWallDistance(int i, int j, int k) {
	return _distance.getScalar(i, j, k);
}

FLOAT *& TurbulentFlowField::getCenterLineVelocity(){
	  return _centerLineBuffer;
}

TurbulentFlowField::~TurbulentFlowField (){
	//delete [] _centerLineBuffer;
}
