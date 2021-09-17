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
  [./Eeqv_t]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Eeqv_i]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Eeqv_c]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Eeqv_p]
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
  [./Eeqv_t_aux]
    type = GolemMFrontEqvStrainAux
    variable = Eeqv_t
    execute_on = 'TIMESTEP_END'
  [../]
  [./Eeqv_i_aux]
    type = GolemMFrontEqvStrainAux
    variable = Eeqv_i
    strain_type = inelastic
    execute_on = 'TIMESTEP_END'
  [../]
  [./Eeqv_c_aux]
    type = MaterialRealAux
    variable = Eeqv_c
    property = eq_viscous_strain
    execute_on = 'TIMESTEP_END'
  [../]
  [./Eeqv_p_aux]
    type = MaterialRealAux
    variable = Eeqv_p
    property = eq_plastic_strain
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
  [./visco_elastic_plastic]
    type = MFrontViscoPlasticity
    mfront_lib_name = '/home/cacace/projects/golem_devel/plugins/mfront/src/libBehaviour.so'
    bulk_modulus = 1.0e+12
    shear_modulus = 1.0e+10
    # young_modulus = 8e9
    # poisson_ratio = 0.3
    phi_angle = 0
    psi_angle = 0
    coh = 26e7
    convert_to_radians = true
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
  [./Eeqv_t]
    type = ElementAverageValue
    variable = Eeqv_t
    outputs = csv
  [../]
  [./Eeqv_i]
    type = ElementAverageValue
    variable = Eeqv_i
    outputs = csv
  [../]
  [./Eeqv_v]
    type = ElementAverageValue
    variable = Eeqv_c
    outputs = csv
  [../]
  [./Eeqv_p]
    type = ElementAverageValue
    variable = Eeqv_p
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
  # csv = true
  [./csv]
    type = Gnuplot
  [../]
[]
