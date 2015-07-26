//////////////////////////////////////////////////////////////////////////////////////////////
/// \file Transformation.hpp
/// \brief Header file for a transformation matrix class.
/// \details Light weight transformation class, intended to be fast, and not to provide
///          unnecessary functionality.
///
/// \author Kai van Es
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
///
/// A note on EIGEN_MAKE_ALIGNED_OPERATOR_NEW (Sean Anderson, as of May 23, 2013)
/// (also see http://eigen.tuxfamily.org/dox-devel/group__TopicStructHavingEigenMembers.html)
///
/// Fortunately, Eigen::Matrix3d and Eigen::Vector3d are NOT 16-byte vectorizable,
/// therefore this class should not require alignment, and can be used normally in STL.
///
/// To inform others of the issue, classes that include *fixed-size vectorizable Eigen types*,
/// see http://eigen.tuxfamily.org/dox-devel/group__TopicFixedSizeVectorizable.html,
/// must include the above macro! Furthermore, special considerations must be taken if
/// you want to use them in STL containers, such as std::vector or std::map.
/// The macro overloads the dynamic "new" operator so that it generates
/// 16-byte-aligned pointers, this MUST be in the public section of the header!
///
//////////////////////////////////////////////////////////////////////////////////////////////

#ifndef LGMATH_TRANSFORMATIONWITHCOVARIANCE_HPP
#define LGMATH_TRANSFORMATIONWITHCOVARIANCE_HPP


#include <lgmath/se3/Transformation.hpp>
#include <Eigen/Core>

namespace lgmath {
    namespace se3 {

        class TransformationWithCovariance: public Transformation
        {
        public:
            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Default constructor
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance();

            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Copy constructor
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance(const TransformationWithCovariance& T);


            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Copy constructor from deterministic Transformation
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance(const Transformation& T, bool covarianceSet = false);

            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Copy constructor from deterministic Transformation, with covariance
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance(const Transformation& T, const Eigen::Matrix<double,6,6>& U);


            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Constructor
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance(const Eigen::Matrix4d& T, bool reproj = true);

            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Constructor with covariance
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance(const Eigen::Matrix4d& T, const Eigen::Matrix<double,6,6>& U,
                                         bool reproj = true);


            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Constructor. The transformation will be T_ba = [C_ba, -C_ba*r_ba_ina; 0 0 0 1]
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance(const Eigen::Matrix3d& C_ba, const Eigen::Vector3d& r_ba_ina,
                                         bool reproj = true);

            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Constructor with covariance. The transformation will be
            /// T_ba = [C_ba, -C_ba*r_ba_ina; 0 0 0 1]
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance(const Eigen::Matrix3d& C_ba, const Eigen::Vector3d& r_ba_ina,
                                         const Eigen::Matrix<double,6,6>& U, bool reproj = true);


            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Constructor. The transformation will be T_ba = vec2tran(xi_ab)
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance(const Eigen::Matrix<double,6,1>& xi_ab,
                                         unsigned int numTerms = 0);

            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Constructor with covariance. The transformation will be T_ba = vec2tran(xi_ab)
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance(const Eigen::Matrix<double,6,1>& xi_ab,
                                         const Eigen::Matrix<double,6,6>& U,
                                         unsigned int numTerms = 0);


            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Constructor. The transformation will be T_ba = vec2tran(xi_ab), xi_ab must be 6x1
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance(const Eigen::VectorXd& xi_ab);

            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Constructor. The transformation will be T_ba = vec2tran(xi_ab), xi_ab must be 6x1
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance(const Eigen::VectorXd& xi_ab,
                                         const Eigen::Matrix<double,6,6>& U);


            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Destructor
            //////////////////////////////////////////////////////////////////////////////////////////////
            ~TransformationWithCovariance() {}

            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Assignment operator. Note pass-by-value is intentional.
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance& operator=(TransformationWithCovariance T);

            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Gets the underlying covariance matrix
            //////////////////////////////////////////////////////////////////////////////////////////////
            const Eigen::Matrix<double,6,6>& U() const;

            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Sets the underlying rotation matrix
            //////////////////////////////////////////////////////////////////////////////////////////////
            void setCovariance(const Eigen::Matrix<double,6,6>& U);

            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Sets the underlying rotation matrix to the 6x6 zero matrix
            //////////////////////////////////////////////////////////////////////////////////////////////
            void zeroCovariance();

            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Get the inverse matrix
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance inverse() const;


            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief In-place right-hand side multiply T_rhs.
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance& operator*=(const TransformationWithCovariance& T_rhs);

            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief In-place right-hand side multiply deterministic T_rhs
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance& operator*=(const Transformation& T_rhs);


            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief In-place right-hand side multiply this matrix by the inverse of T_rhs
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance& operator/=(const TransformationWithCovariance& T_rhs);

            //////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief In-place right-hand side multiply this matrix by the inverse of deterministic T_rhs
            //////////////////////////////////////////////////////////////////////////////////////////////
            TransformationWithCovariance& operator/=(const Transformation& T_rhs);

        private:

            //////////////////////////////////////////////////////////////////////////////////////////////
            /// Covariance
            //////////////////////////////////////////////////////////////////////////////////////////////
            Eigen::Matrix<double,6,6> U_;

            //////////////////////////////////////////////////////////////////////////////////////////////
            /// Covariance flag.  Set to true when the covariance is manually set or initialized.
            //////////////////////////////////////////////////////////////////////////////////////////////
            bool covarianceSet_;
        };


        //////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Multiplication of TransformWithCovariance by TransformWithCovariance
        //////////////////////////////////////////////////////////////////////////////////////////////
        TransformationWithCovariance operator*(TransformationWithCovariance T_lhs,
                                               const TransformationWithCovariance& T_rhs);

        //////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Multiplication of TransformWithCovariance by Transform
        //////////////////////////////////////////////////////////////////////////////////////////////
        TransformationWithCovariance operator*(TransformationWithCovariance T_lhs,
                                               const Transformation& T_rhs);

        //////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Multiplication of Transform by TransformWithCovariance
        //////////////////////////////////////////////////////////////////////////////////////////////
        TransformationWithCovariance operator*(const Transformation& T_lhs,
                                               const TransformationWithCovariance& T_rhs);


        //////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Multiplication of TransformWithCovariance by inverse TransformWithCovariance
        //////////////////////////////////////////////////////////////////////////////////////////////
        TransformationWithCovariance operator/(TransformationWithCovariance T_lhs,
                                               const TransformationWithCovariance& T_rhs);

        //////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Multiplication of TransformWithCovariance by inverse Transform
        //////////////////////////////////////////////////////////////////////////////////////////////
        TransformationWithCovariance operator/(TransformationWithCovariance T_lhs,
                                               const Transformation& T_rhs);

        //////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Multiplication of Transform by inverse TransformWithCovariance
        //////////////////////////////////////////////////////////////////////////////////////////////
        TransformationWithCovariance operator/(const Transformation& T_lhs,
                                               const TransformationWithCovariance& T_rhs);

    } // se3
} // lgmath


//////////////////////////////////////////////////////////////////////////////////////////////
/// \brief print transformation
//////////////////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& out, const lgmath::se3::TransformationWithCovariance& T);


#endif //LGMATH_TRANSFORMATIONWITHCOVARIANCE_HPP


