m.def("vertex_components", []
(
	const Eigen::MatrixXi& F,
	Eigen::MatrixXi& C
	)
	{
		return igl::vertex_components(F, C);
	},
	py::arg("F"), py::arg("C"));