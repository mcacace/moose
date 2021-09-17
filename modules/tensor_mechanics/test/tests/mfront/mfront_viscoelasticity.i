# benchmark: quasi-static stress build-up for a Maxwell rheology
# set up from Gerya and Yuen[2007] first example
# pure shear --> compression across the right and extension across the bottom
# the original set up requires an incompressible material
# here the bulk modulus is set to 1e12 Pa to fake incompressibility
# analytical solution:
# sigma = 2 * eps_dot * eta * (1 - exp(-G*t/eta))

[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  xmin = 0
  xmax = 1
  ymin = 0
  ymax = 1
[]

[Variables]
  [./disp_x]
  [../]
  [./disp_y]
  [../]
[]

[GlobalParams]
  displacements = 'disp_x disp_y'
  scaling_uo = scaling
[]

[Kernels]
  [./mech_x]
    type = GolemMFrontKernelM
    variable = disp_x
    component = 0
  [../]
  [./mech_y]
    type = GolemMFrontKernelM
    variable = disp_y
    component = 1
  [../]
[]

[AuxVariables]
  [./Se]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./E_eqv]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./E_eqv_creep]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./eta_e]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./Se_aux]
    type = GolemVonMisesStressAux
    variable = Se
    execute_on = 'TIMESTEP_END'
  [../]
  [./E_eqv_aux]
    type = GolemMFrontEqvStrainAux
    variable = E_eqv
    execute_on = 'TIMESTEP_END'
  [../]
  [./E_eqv_creep_aux]
    type = GolemMFrontEqvStrainAux
    variable = E_eqv_creep
    strain_type = viscous
    execute_on = 'TIMESTEP_END'
  [../]
  [./eta_e_aux]
    type = MaterialRealAux
    variable = eta_e
    property = effective_viscosity
    execute_on = 'TIMESTEP_END'
  [../]
[]

[BCs]
  [./no_ux]
    type = DirichletBC
    variable = disp_x
    boundary = left
    value = 0.0
  [../]
  [./ux_right]
    type = GolemVelocityBC
    variable = disp_x
    boundary = right
    velocity = -1.0e-14
  [../]
  [./no_uy]
    type = DirichletBC
    variable = disp_y
    boundary = top
    value = 0.0
  [../]
  [./uy_bottom]
    type = GolemVelocityBC
    variable = disp_y
    boundary = bottom
    velocity = -1.0e-14
  [../]
[]

[Materials]
  [./visco_elastic]
    type = MFrontViscoElasticity
    mfront_lib_name = '/home/cacace/projects/golem_devel/plugins/mfront/src/libBehaviour.so'
    bulk_modulus = 1.0e+12
    shear_modulus = 1.0e+10
    A_creep = 5.0e-23
    n_creep = 1.0
    Q_act = 0.0
  [../]
[]

[UserObjects]
  [./scaling]
    type = GolemScaling
    execute_on = 'INITIAL'
  [../]
[]

[Postprocessors]
  [./S]
    type = ElementAverageValue
    variable = Se
    outputs = csv
  [../]
  [./Eeqv]
    type = ElementAverageValue
    variable = E_eqv
    outputs = csv
  [../]
  [./Eveqv]
    type = ElementAverageValue
    variable = E_eqv_creep
    outputs = csv
  [../]
[]

[Preconditioning]
  active = 'mine'
  [./precond]
    type = SMP
    full = true
    petsc_options = '-snes_ksp_ew'
    petsc_options_iname = '-ksp_type -pc_type -snes_atol -snes_rtol -snes_max_it -ksp_max_it -sub_pc_type -sub_pc_factor_shift_type'
    petsc_options_value = 'gmres asm 1e-15 1e-10 20 50 ilu NONZERO'
  [../]
  [./mine]
    type = SMP
    full = true
    petsc_options = '-snes_ksp_ew'
    petsc_options_iname = '-snes_atol -snes_rtol -snes_max_it
                           -ksp_type -ksp_max_it
                           -pc_type
                           -sub_pc_type -sub_pc_factor_shift_type'
    petsc_options_value = '1e-15 1e-10 20
                          fgmres 1000
                          asm ilu NONZERO'
  [../]
[]

[Executioner]
  type = Transient
  solve_type = 'NEWTON'
  start_time = 0.0
  end_time = 3.1536e+13
  num_steps = 5000
  automatic_scaling = true
  compute_scaling_once = false
[]

[Outputs]
  execute_on = 'INITIAL TIMESTEP_END'
  print_linear_residuals = false
  perf_graph = true
  exodus = false
  csv = true
[]
