extends Node


func _ready():
	var slangGlobalSession = slang_IGlobalSession.new()
	slang_global.createGlobalSession(slangGlobalSession)
	var sessionDesc = slang_SessionDesc.new()
	var targetDesc = slang_TargetDesc.new()
	targetDesc.set_format(6)
	targetDesc.set_profile(slangGlobalSession.findProfile("spirv_1_5"))
	targetDesc.set_flags(1024)
	var vec = slang_TargetDesc_VALUE_VECTOR.new();
	vec.push_back(targetDesc)
	sessionDesc.set_targets(vec)
	sessionDesc.set_targetCount(1)
	var session = slang_ISession.new()
	slangGlobalSession.createSession(sessionDesc,session)
	var diagnosticBlob1 = slang_IBlob.new()
	var path : String = "hello-world.slang"
	var slangModule1 = session.loadModule(path,diagnosticBlob1)
	if(diagnosticBlob1.has_value()):
		print(diagnosticBlob1.getBufferSize())
		print(diagnosticBlob1.getBufferPointer())
	if(!slangModule1.get_value().has_value() || slangModule1.get_value() == null):
		print(-1)
		pass
	var entryPoint = slang_IEntryPoint.new()
	slangModule1.get_value().findEntryPointByName("computeMain",entryPoint)
	
	var componentTypesVec = slang_IComponentType_VECTOR.new()
	var com1 = slang_global.IModule_shiftToComponent(slangModule1.get_value())
	componentTypesVec.push_back(com1.get_value())
	var com2 = slang_global.IEntryPoint_shiftToComponent(entryPoint)
	componentTypesVec.push_back(com2.get_value())
	var composedProgram = slang_IComponentType.new()
	var diagnosticBlob2 = slang_IBlob.new()
	var result : int = session.createCompositeComponentType(componentTypesVec,composedProgram,diagnosticBlob2)
	com1.free_self()
	com2.free_self()
	slangModule1.free_self()
	if(diagnosticBlob2.has_value()):
		print(diagnosticBlob2.getBufferPointer())
	if(result != 0):
		print(-2)
		pass
	var spirvCode = slang_IBlob.new()
	var diagnosticsBlob3 = slang_IBlob.new()
	result = composedProgram.getEntryPointCode(0,0,spirvCode,diagnosticsBlob3)
	
	if(diagnosticsBlob3.has_value()):
		print(diagnosticsBlob3.getBufferPointer())
	if(result != 0):
		print(-3)
		pass
	var layout = composedProgram.getLayout(0,null)
	var parameterCount = layout.get_value().getParameterCount()
	for pp in range(0,parameterCount,1):
		var parameter = layout.get_value().getParameterByIndex(pp)
		print("Parameter[",pp,"]:",parameter.get_value().getName(),"\n")
		print("-Offset:%d\n"%parameter.get_value().getOffset(8))
		print("-Index:%d\n"%parameter.get_value().getBindingIndex())
		parameter.free_self()
	layout.free_self()
	print("Generated SpirV Code: %d B\n"%spirvCode.getBufferSize());
	
	var file = FileAccess.open("res://output.spv", FileAccess.WRITE)
	file.store_string(spirvCode.getBufferPointer())
	pass
