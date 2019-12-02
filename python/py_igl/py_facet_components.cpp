m.def("facet_components", []
(
	const Eigen::MatrixXi& F,
	Eigen::MatrixXi& C
	)
	{
		Eigen::VectorXi C_;
		igl::facet_components(F, C_);
		C = C_;
	},
	py::arg("F"), py::arg("C"));