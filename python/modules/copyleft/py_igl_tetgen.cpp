// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2017 Sebastian Koch <s.koch@tu-berlin.de> and Daniele Panozzo <daniele.panozzo@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
//#include <Eigen/Geometry>
//#include <Eigen/Dense>
//#include <Eigen/Sparse>


#include "../../python_shared.h"

#include <igl/copyleft/tetgen/tetrahedralize.h>
#include  <igl/list_to_matrix.h>
#include  <igl/matrix_to_list.h>
#include <igl/copyleft/tetgen/mesh_to_tetgenio.h>
#include <igl/copyleft/tetgen/tetgenio_to_tetmesh.h>

// IGL_INLINE int igl::copyleft::tetgen::tetrahedralize(
// 	const std::vector<std::vector<REAL > >& V,
// 	const std::vector<std::vector<int> >& F,
// 	const std::vector<std::vector<REAL > >& H,
// 	const std::vector<std::vector<REAL > >& R,
// 	const std::string switches,
// 	std::vector<std::vector<REAL > >& TV,
// 	std::vector<std::vector<int > >& TT,
// 	std::vector<std::vector<int > >& TF,
// 	std::vector<std::vector<REAL > >& TR,
// 	std::vector<std::vector<int > >& TN,
// 	std::vector<std::vector<int > >& PT,
// 	std::vector<std::vector<int > >& FT,
// 	size_t& numRegions)
// {
// 	using namespace std;
// 	tetgenio in, out;
// 	bool success;
// 	success = mesh_to_tetgenio(V, F, H, R, in);
// 	if (!success)
// 	{
// 		return -1;
// 	}
// 	try
// 	{
// 		char* cswitches = new char[switches.size() + 1];
// 		strcpy(cswitches, switches.c_str());
//
// 		::tetrahedralize(cswitches, &in, &out);
// 		delete[] cswitches;
// 	}
// 	catch (int e)
// 	{
// 		cerr << "^" << __FUNCTION__ << ": TETGEN CRASHED...KABOOM!!" << endl;
// 		return 1;
// 	}
// 	if (out.numberoftetrahedra == 0)
// 	{
// 		cerr << "^" << __FUNCTION__ << ": Tetgen failed to create tets" << endl;
// 		return 2;
// 	}
// 	success = tetgenio_to_tetmesh(out, TV, TT, TF, TR, TN, PT, FT, numRegions
// 	);
// 	if (!success)
// 	{
// 		return -1;
// 	}
// 	return 0;
// }

template <
	typename DerivedV,
	typename DerivedF,
	typename DerivedH,
	typename DerivedR,
	typename DerivedTV,
	typename DerivedTT,
	typename DerivedTF,
	typename DerivedTR>
	IGL_INLINE int igl::copyleft::tetgen::tetrahedralize(
		const Eigen::PlainObjectBase<DerivedV>& V,
		const Eigen::PlainObjectBase<DerivedF>& F,
		const Eigen::PlainObjectBase<DerivedH>& H,
		const Eigen::PlainObjectBase<DerivedR>& R,
		const std::string switches,
		Eigen::PlainObjectBase<DerivedTV>& TV,
		Eigen::PlainObjectBase<DerivedTT>& TT,
		Eigen::PlainObjectBase<DerivedTF>& TF,
		Eigen::PlainObjectBase<DerivedTR>& TR,
		Eigen::PlainObjectBase<DerivedTT>& TN,
		Eigen::PlainObjectBase<DerivedTT>& PT,
		Eigen::PlainObjectBase<DerivedTT>& FT,
		size_t& numRegions)
{
	using namespace std;
	vector<vector<REAL> > vV, vH, vR, vTV, vTR;
	vector<vector<int> > vF, vTT, vTF, vTN, vPT, vFT;
	matrix_to_list(V, vV);
	matrix_to_list(F, vF);
	matrix_to_list(H, vH);
	matrix_to_list(R, vR);

	int e = tetrahedralize(vV, vF, vH, vR, switches, vTV, vTT, vTF, vTR, vTN, vPT, vFT, numRegions);

	if (e == 0)
	{
		bool TV_rect = list_to_matrix(vTV, TV);
		if (!TV_rect)
		{
			return 3;
		}
		bool TT_rect = list_to_matrix(vTT, TT);
		if (!TT_rect)
		{
			return 3;
		}
		bool TF_rect = list_to_matrix(vTF, TF);
		if (!TF_rect)
		{
			return 3;
		}
		bool TR_rect = list_to_matrix(vTR, TR);
		if (!TR_rect)
		{
			return 3;
		}
		bool TN_rect = list_to_matrix(vTN, TN);
		if (!TN_rect)
		{
			return 3;
		}
		bool PT_rect = list_to_matrix(vPT, PT);
		if (!PT_rect)
		{
			return 3;
		}
		bool FT_rect = list_to_matrix(vFT, FT);
		if (!FT_rect)
		{
			return 3;
		}
	}
	return e;
}


void python_export_igl_tetgen(py::module &me) {

  py::module m = me.def_submodule(
    "tetgen", "Wrappers for libigl functions that use tetgen");

  #include "../../py_igl/copyleft/tetgen/py_tetrahedralize.cpp"

}
