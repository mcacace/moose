# Testing the MFront Interface
# linear elastic model using small strain formulation.

[GlobalParams]
  displacements = 'disp_x disp_y disp_z'
[]

[Mesh]
  [gen]
    type = GeneratedMeshGenerator
    dim = 3
    xmin = -0.5
    xmax = 0.5
    ymin = -0.5
    ymax = 0.5
    zmin = -0.5
    zmax = 0.5
    nx = 10
    ny = 10
    nz = 10
  []
[]

[Functions]
  [top_pull]
    type = ParsedFunction
    value = t/100
  []
[]

[Modules/TensorMechanics/Master]
  [all]
    add_variables = true
    strain = SMALL
    incremental = true
  []
[]

[BCs]
  [y_pull_function]
    type = FunctionDirichletBC
    variable = disp_y
    boundary = top
    function = top_pull
  []
  [x_bot]
    type = DirichletBC
    variable = disp_x
    boundary = left
    value = 0.0
  []
  [y_bot]
    type = DirichletBC
    variable = disp_y
    boundary = bottom
    value = 0.0
  []
  [z_bot]
    type = DirichletBC
    variable = disp_z
    boundary = front
    value = 0.0
  []
[]

[Materials]
  [elastic]
    type = ComputeIsotropicElasticityTensor
    youngs_modulus = 1000
    poissons_ratio = 0.3
  []
  [stress]
    type = ComputeFiniteStrainElasticStress
  []
[]

[AuxVariables]
  [stress_00]
    order = CONSTANT
    family = MONOMIAL
  []
  [stress_11]
    order = CONSTANT
    family = MONOMIAL
  []
  [stress_22]
    order = CONSTANT
    family = MONOMIAL
  []
  [stress_01]
    order = CONSTANT
    family = MONOMIAL
  []
  [stress_02]
    order = CONSTANT
    family = MONOMIAL
  []
  [stress_12]
    order = CONSTANT
    family = MONOMIAL
  []
[]

[AuxKernels]
  [stress_00_aux]
    type = RankTwoAux
    variable = stress_00
    rank_two_tensor = stress
    index_i = 0
    index_j = 0
    execute_on = 'TIMESTEP_END'
  []
  [stress_11_aux]
    type = RankTwoAux
    variable = stress_11
    rank_two_tensor = stress
    index_i = 1
    index_j = 1
    execute_on = 'TIMESTEP_END'
  []
  [stress_22_aux]
    type = RankTwoAux
    variable = stress_22
    rank_two_tensor = stress
    index_i = 2
    index_j = 2
    execute_on = 'TIMESTEP_END'
  []
  [stress_01_aux]
    type = RankTwoAux
    variable = stress_01
    rank_two_tensor = stress
    index_i = 0
    index_j = 1
    execute_on = 'TIMESTEP_END'
  []
  [stress_02_aux]
    type = RankTwoAux
    variable = stress_02
    rank_two_tensor = stress
    index_i = 0
    index_j = 2
    execute_on = 'TIMESTEP_END'
  []
  [stress_12_aux]
    type = RankTwoAux
    variable = stress_12
    rank_two_tensor = stress
    index_i = 1
    index_j = 2
    execute_on = 'TIMESTEP_END'
  []
[]

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
  print_linear_residuals = false
  [perf_graph]
    type = PerfGraphOutput
    heaviest_branch = true
    level = 2
    heaviest_sections = 2
    execute_on = 'FINAL'
  []
[]
