# type: axial tensile loading - no confinement
# material: Ramberg-Osgood non linear elasticity

[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 10
  ny = 10
  nz = 20
  xmin = 0
  xmax = 0.5
  ymin = 0
  ymax = 0.5
  zmin = 0
  zmax = 1
[]

[GlobalParams]
  displacements = 'disp_x disp_y disp_z'
[]

[Modules/TensorMechanics/Master]
  [all]
    add_variables = true
    strain = SMALL
    incremental = true
  []
[]

# [Functions]
#   [push]
#     type = ParsedFunction
#     value = 'if(t<=50,load,if(t>50&t<80,unload,if(t>=80&t<=130,load,if(t>130&t<160,unload,load))))'
#     vars = 'load unload'
#     vals = '-7.5e-6 v_unload'
#   []
#   [v_unload]
#     type = ParsedFunction
#     value = 'v0/a'
#     vars = 'v0 a'
#     vals = '7.5e-6 1'
#   []
# []

[BCs]
  [./no_x]
    type = DirichletBC
    variable = disp_x
    boundary = 'left right'
    value = 0.0
  [../]
  [./no_y]
    type = DirichletBC
    variable = disp_y
    boundary = 'bottom top'
    value = 0.0
  [../]
  # [./no_z_back]
  #   type = DirichletBC
  #   variable = disp_z
  #   boundary = 'back'
  #   value = 0.0
  # [../]
  [./load_z_front]
    type = PresetVelocity
    variable = disp_z
    boundary = 'front'
    # function = push
    velocity = 7.5e-6
  [../]
  [./load_z_back]
    type = PresetVelocity
    variable = disp_z
    boundary = 'back'
    # function = push
    velocity = -7.5e-6
  [../]
[]

[Materials]
  [plastic]
    type = MFrontRambergOsgoodNonLinearElasticity
    young_modulus = 1000
    poisson_ratio = 0.25
    n = 5
    alpha = 100
    yield_strength = 1
    mfront_lib_name = '../../../plugins/MFront/src/libBehaviour.so'
  []
[]

[AuxVariables]
  [stress_zz]
    order = CONSTANT
    family = MONOMIAL
  []
  # [elastic_strain_zz]
  #   order = CONSTANT
  #   family = MONOMIAL
  # []
  [total_strain_zz]
    order = CONSTANT
    family = MONOMIAL
  []
[]

[AuxKernels]
  [stress_zz_aux]
    type = RankTwoAux
    variable = stress_zz
    rank_two_tensor = stress
    index_i = 2
    index_j = 2
    execute_on = 'TIMESTEP_END'
  []
  # [elastic_strain_zz_aux]
  #   type = RankTwoAux
  #   variable = elastic_strain_zz
  #   rank_two_tensor = elastic_strain
  #   index_i = 2
  #   index_j = 2
  #   execute_on = 'TIMESTEP_END'
  # []
  [total_strain_zz_aux]
    type = RankTwoAux
    variable = total_strain_zz
    rank_two_tensor = total_strain
    index_i = 2
    index_j = 2
    execute_on = 'TIMESTEP_END'
  []
[]

[Postprocessors]
  [./u_z]
    type = SideAverageValue
    variable = disp_z
    boundary = right
    outputs = csv
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
  [./S_zz]
    type = ElementAverageValue
    variable = stress_zz
    outputs = csv
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
  # [./Es_zz]
  #   type = ElementAverageValue
  #   variable = elastic_strain_zz
  #   outputs = csv
  #   execute_on = 'INITIAL TIMESTEP_END'
  # [../]
  [./E_zz]
    type = ElementAverageValue
    variable = total_strain_zz
    outputs = csv
    execute_on = 'INITIAL TIMESTEP_END'
  [../]
[]

[Preconditioning]
  [./precond]
    type = SMP
    full = true
    petsc_options_iname = '-pc_type -pc_hypre_type'
    petsc_options_value = 'hypre boomeramg'
  [../]
[]

[Executioner]
  type = Transient
  solve_type = 'NEWTON'
  automatic_scaling = true
  start_time = 0.0
  end_time = 210.0
  dt = 2.0
  nl_abs_tol = 1e-15
[]

[Outputs]
  execute_on = 'timestep_end'
  print_linear_residuals = false
  perf_graph = true
  exodus = true
  csv = true
[]
