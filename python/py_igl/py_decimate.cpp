// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2017 Sebastian Koch <s.koch@tu-berlin.de> and Daniele Panozzo <daniele.panozzo@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

m.def("decimate", []
(
	const Eigen::MatrixXd& V,
	const Eigen::MatrixXi& F,
	const int max_m,
	Eigen::MatrixXd& U,
	Eigen::MatrixXi& G
)
{
	Eigen::VectorXi J;
	return igl::decimate(V, F, max_m, U, G, J);
}, //__doc_igl_decimate,
py::arg("V"), py::arg("F"), py::arg("max_m"), py::arg("U"), py::arg("G"));