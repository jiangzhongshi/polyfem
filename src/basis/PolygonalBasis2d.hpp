#ifndef POLYGONAL_BASIS_HPP
#define POLYGONAL_BASIS_HPP

#include <polyfem/CMesh2D.hpp>
#include <polyfem/NCMesh2D.hpp>
#include <polyfem/AssemblerUtils.hpp>
#include <polyfem/ElementBases.hpp>
#include <polyfem/ElementAssemblyValues.hpp>
#include <polyfem/InterfaceData.hpp>

#include <Eigen/Dense>
#include <vector>
#include <map>

namespace polyfem
{

	class PolygonalBasis2d
	{
	public:
		// Compute the integral constraints for each basis of the mesh. This step is PDE-dependent.
		//
		// @param[in]  mesh             Input surface mesh
		// @param[in]  n_bases          Number of bases/nodes in the mesh
		// @param[in]  values           Shape functions for the PDE field evaluated over each
		//                              elements
		// @param[in]  gvalues          Shape functions for the geometric mapping evaluated over
		//                              each elements
		// @param[out] basis_integrals  Integral constraints over polygon that each basis of the
		//                              mesh must verify
		//
		static void compute_integral_constraints(
			const AssemblerUtils &assembler,
			const std::string &assembler_name,
			const Mesh2D &mesh,
			const int n_bases,
			const std::vector<ElementBases> &bases,
			const std::vector<ElementBases> &gbases,
			Eigen::MatrixXd &basis_integrals);

		///
		/// @brief         Build bases over the remaining polygons of a mesh.
		///
		/// @param[in]     n_samples_per_edge    { Number of collocation samples per polygon edge
		///                                      (including endpoints) }
		/// @param[in]     mesh                  { Input surface mesh }
		/// @param[in]     n_bases               { Total number of bases functions in the mesh }
		/// @param[in]     quadrature_order      { Quadrature order for the polygons }
		/// @param[in]     integral_constraints  { Order of the integral constraints (0 = no
		///                                      constraints, 1 = linear, 2 = quadratic) }
		/// @param[in,out] bases                 { List of the different basis (shape functions)
		///                                      used to discretize the PDE }
		/// @param[in]     gbases                { List of the different basis used to discretize
		///                                      the geometry of the mesh }
		/// @param[in]     poly_edge_to_data     { Additional data computed for edges at the
		///                                      interface with a polygon }
		/// @param[out]    mapped_boundary       { Map element id -> #S x dim polyline formed by the
		///                                      collocation points on the boundary of the polygon.
		///                                      The collocation points are mapped through the
		///                                      geometric mapping of the element across the edge,
		///                                      so this polyline may differ from the original
		///                                      polygon. }
		/// @param[in]  element_types  { Per-element tag indicating the type of each element (see Mesh.hpp) }
		/// @param[in]  values         { Per-element shape functions for the PDE, evaluated over the element,
		///                            used for the system matrix assembly (used for linear reproduction) }
		/// @param[in]  gvalues        { Per-element shape functions for the geometric mapping, evaluated over
		///                            the element (get boundary of the polygon) }
		///
		static int build_bases(
			const AssemblerUtils &assembler,
			const std::string &assembler_name,
			const int n_samples_per_edge,
			const Mesh2D &mesh,
			const int n_bases,
			const int quadrature_order,
			const int integral_constraints,
			std::vector<ElementBases> &bases,
			const std::vector<ElementBases> &gbases,
			const std::map<int, InterfaceData> &poly_edge_to_data,
			std::map<int, Eigen::MatrixXd> &mapped_boundary);
	};
} // namespace polyfem
#endif //POLYGONAL_BASIS_HPP
