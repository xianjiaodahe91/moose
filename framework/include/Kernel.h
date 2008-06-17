// libMesh includes
#include "equation_systems.h"
#include "mesh_base.h"
#include "nonlinear_implicit_system.h"
#include "fe_base.h"
#include "quadrature_gauss.h"
#include "auto_ptr.h"

//Forward Declarations
class Elem;

/** 
 * The Kernel class is responsible for calculating the residuals for various
 * physics.
 * 
 */
class Kernel
{
public:
  /** 
   * This constructor should be used most often.  It initializes all internal
   * references needed for residual computation.
   * 
   * @param system The system this variable is in
   * @param var_name The variable this Kernel is going to compute a residual for.
   */
  Kernel(EquationSystems * es, std::string var_name);

  virtual ~Kernel(){};

  /** 
   * Computes the residual for the current element.
   * 
   * @param Re Local residual vector.
   * @param elem Current element.
   */
  void computeElemResidual(const NumericVector<Number>& soln, DenseVector<Number> & Re, Elem * elem);

protected:
  
  /** 
   * This is the virtual that derived classes should override.
   */
  virtual Real computeQpResidual();

  /**
   * Holds the current solution at the current quadrature point.
   */
  Real _u;

  /**
   * Holds the current solution gradient at the current quadrature point.
   */
  RealGradient _grad_u;

  EquationSystems & _es;
  std::string _var_name;

  MeshBase & _mesh;
  unsigned int _dim;

  NonlinearImplicitSystem & _system;
  const DofMap & _dof_map;
  std::vector<unsigned int> _dof_indices;

  /**
   * FE Type to be used.
   */
  FEType _fe_type;

  /**
   * Interior finite element.
   */
  AutoPtr<FEBase> _fe;

  /**
   * Interior quadrature rule.
   */
  QGauss _qrule;

  /**
   * Current _qrule quadrature point.
   */
  unsigned int _qp;

  /**
   * Boundary finite element. 
   */
  AutoPtr<FEBase> _fe_face;

  /**
   * Boundary quadrature rule.
   */
  QGauss _qface;

  /**
   * Interior Jacobian pre-multiplied by the weight.
   */
  const std::vector<Real> & _JxW;

  /**
   * Interior shape function.
   */
  const std::vector<std::vector<Real> > & _phi;

  /**
   * Gradient of interior shape function.
   */
  const std::vector<std::vector<RealGradient> > & _dphi;

  /**
   * Current shape function.
   */
  unsigned int _i;  
};

