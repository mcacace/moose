# Testing the MFront Interface
# linear elastic model using small strain formulation - 3D case.

[GlobalParams]
  displacements = 'disp_x disp_y disp_z'
[]

[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 1 #8
  ny = 1 #8
  nz = 1 #2
  xmin = 0
  xmax = 10
  ymin = 0
  ymax = 10
  zmin = 0
  zmax = 2.5
[]

[Modules/TensorMechanics/Master]
  [all]
    add_variables = true
    strain = SMALL
    incremental = true
  []
[]

[BCs]
  [./no_x]
    type = DirichletBC
    variable = disp_x
    boundary = 'left right bottom top front back'
    value = 0.0
  [../]
  [./no_z]
    type = DirichletBC
    variable = disp_z
    boundary = 'left right bottom top front back'
    value = 0.0
  [../]
  [./disp_y_plate]
    type = FunctionDirichletBC
    variable = disp_y
    boundary = 'left right bottom top front back'
    function = disp_y_func
  [../]
[]

[Materials]
  [mfront]
    type = MFrontLinearElasticity
    young_modulus = 10.0e+09
    poisson_ratio = 0.25
    mfront_lib_name = '../../../plugins/MFront/src/libBehaviour.so'
  []
[]

[AuxVariables]
  [stress_01]
    order = CONSTANT
    family = MONOMIAL
  []
  [strain_01]
    order = CONSTANT
    family = MONOMIAL
  []
  [strain_analytical]
    order = CONSTANT
    family = MONOMIAL
  []
  [stress_analytical]
    order = CONSTANT
    family = MONOMIAL
  []
[]

[AuxKernels]
  [strain_analytical_aux]
    type = FunctionAux
    variable = strain_analytical
    function = strain_xy_analytical
  []
  [stress_analytical_aux]
    type = FunctionAux
    variable = stress_analytical
    function = stress_xy_analytical
  []
  [stress_01_aux]
    type = RankTwoAux
    variable = stress_01
    rank_two_tensor = stress
    index_i = 0
    index_j = 1
    execute_on = 'TIMESTEP_END'
  []
  [strain_01_aux]
    type = RankTwoAux
    variable = strain_01
    rank_two_tensor = total_strain
    index_i = 0
    index_j = 1
    execute_on = 'TIMESTEP_END'
  []
[]

[Functions]
  [./disp_y_func]
    type = ParsedFunction
    value = 'm*t*x'
    vars = 'm'
    vals = '-0.1'
  [../]
  [./strain_xy_analytical]
   type = ParsedFunction
   value = 'm*t/2'
   vars = 'm'
   vals = '-0.1'
  [../]
  [./stress_xy_analytical]
   type = ParsedFunction
   value = 'E/(2*(1+nu))*m*t'
   vars = 'm E nu'
   vals = '-0.1 10.0e+09 0.25'
  [../]
[]

# [Postprocessors]
#  # [./error_exy]
#  #   type = ElementL2Difference
#  #   variable = strain_01
#  #   other_variable = strain_analytical
#  #   outputs = csv
#  # [../]
#  # [./error_sxy]
#  #   type = ElementL2Difference
#  #   variable = stress_01
#  #   other_variable = stress_analytical
#  #   outputs = csv
#  # [../]
#  [./strain_pp]
#    type = ElementAverageValue
#    variable = strain_01
#    outputs = csv
#   execute_on = 'INITIAL TIMESTEP_END'
#  [../]
#  [./stress_pp]
#    type = ElementAverageValue
#    variable = stress_01
#    outputs = csv
#    execute_on = 'INITIAL TIMESTEP_END'
#  [../]
# []

[Executioner]
  type = Transient
  solve_type = 'NEWTON'

  petsc_options = '-snes_ksp_ew'
  petsc_options_iname = '-ksp_gmres_restart'
  petsc_options_value = '101'

  line_search = 'none'

  l_max_its = 100
  nl_max_its = 100
  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-10
  l_tol = 1e-9
  start_time = 0.0
  num_steps = 30
  dt = 1.0
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

[Outputs]
  exodus = true
  csv = true
  print_linear_residuals = false
  [perf_graph]
    type = PerfGraphOutput
    heaviest_branch = true
    level = 2
    heaviest_sections = 2
    execute_on = 'FINAL'
  []
[]
