#tag Class
Protected Class clEventlessScript
	#tag Method, Flags = &h0
		Sub BuildErrorDictionary()
		  
		  dmsg = new Dictionary
		  
		  
		  dmsg.value(1)="Syntax error."
		  dmsg.value(2)="Type mismatch error."
		  dmsg.value(3)="Only modules can be imported, but this is not a module."
		  dmsg.value(4)="Can't import symbols over an existing symbol."
		  dmsg.value(5)="The parser's internal stack has overflowed."
		  dmsg.value(6)="Too many parameters for this function."
		  dmsg.value(7)="Not enough parameters for this function call."
		  dmsg.value(8)="Wrong number of parameters for this function call."
		  dmsg.value(9)="Parameters are incompatible with this function."
		  dmsg.value(10)="Assignment of an incompatible data type."
		  dmsg.value(11)="Undefined identifier."
		  dmsg.value(12)="Undefined operator."
		  dmsg.value(13)="Logic operations require Boolean operands."
		  dmsg.value(14)="Array bounds must be integers."
		  dmsg.value(15)="Can't call something that isn't a function."
		  dmsg.value(16)="This is not an array but you are using it as one."
		  dmsg.value(17)="This array has more dimensions than you have provided."
		  dmsg.value(18)="This array has fewer dimensions than you have provided."
		  dmsg.value(19)="Can't assign an entire array."
		  dmsg.value(20)="Can't use an entire array in an expression."
		  dmsg.value(21)="You can't pass an expression as a parameter that is defined as ByRef."
		  dmsg.value(22)="Redefined identifier."
		  dmsg.value(23)="The backend code generator failed."
		  dmsg.value(24)="Ambiguous call to overloaded method."
		  dmsg.value(25)="Multiple inheritance is not allowed."
		  dmsg.value(26)="You cannot create an instance of interface with New because it is not a class."
		  dmsg.value(27)="One of the interfaces of this class is not of type class interface."
		  dmsg.value(28)="You can only inherit from a class."
		  dmsg.value(29)="This class does not fully implement the specified interface."
		  dmsg.value(30)="Event handlers cannot live outside of a class."
		  dmsg.value(31)="You must use the value returned by this function."
		  dmsg.value(32)="'Self' doesn't mean anything in a module method."
		  dmsg.value(33)="'Me' doesn't mean anything in a module method."
		  dmsg.value(34)="You cannot return a value because this method has not defined a return type."
		  dmsg.value(35)="Exception objects must be subclasses of RuntimeException."
		  dmsg.value(36)="Return type does not match the interface method's return type."
		  dmsg.value(37)="Return type does not match overridden method's return type."
		  dmsg.value(38)="You cannot implement a nonexistent event."
		  dmsg.value(39)="You cannot implement a nonexistent event."
		  dmsg.value(40)="Destructors can't have parameters."
		  dmsg.value(41)="Modules do not have superclasses. So 'Super' does not mean anything in a module method."
		  dmsg.value(42)="The current class does not have a superclass, so 'Super' does not mean anything in this method."
		  dmsg.value(43)="This #else does not have a matching #if preceding it."
		  dmsg.value(44)="This #endif does not have a matching #if preceding it."
		  dmsg.value(45)="Only Boolean constants can be used with #if."
		  dmsg.value(46)="Only constants expressions can be used with #if."
		  dmsg.value(47)="The Next variable does not match the loop's counter variable."
		  dmsg.value(48)="The size of an array must be a constant or number."
		  dmsg.value(49)="You can't pass an array to an external function."
		  dmsg.value(50)="External functions cannot use objects as parameters."
		  dmsg.value(51)="External functions cannot use ordinary strings as parameters. Use CString, PString, WString, or CFStringRef instead."
		  dmsg.value(52)="This kind of array can not be sorted."
		  dmsg.value(53)="This property is protected. It can only be used from within its class."
		  dmsg.value(54)="This method is protected. It can only be called from within its class."
		  dmsg.value(55)="This local variable or constant has the same name as a Declare in this method. You must resolve this conflict."
		  dmsg.value(56)="This global variable has the same name as a global function."
		  dmsg.value(57)="This property has the same name as a method. You must resolve this conflict."
		  dmsg.value(58)="This property has the same name as an event. You must resolve this conflict."
		  dmsg.value(59)="This global variable has the same name as a class."
		  dmsg.value(60)="This global variable has the same name as a module."
		  dmsg.value(61)="This local variable or parameter has the same name as a constant. You must resolve this conflict."
		  dmsg.value(62)="This identifier is reserved and can't be used as a variable or property name."
		  dmsg.value(63)="There is no class with this name. Can't find a type with this name."
		  dmsg.value(64)="The library name must be a string constant."
		  dmsg.value(65)="This Declare Function statement is missing its return type."
		  dmsg.value(66)="You can't use the New operator with this class."
		  dmsg.value(67)="This method doesn't return a value."
		  dmsg.value(68)="End quote missing."
		  dmsg.value(69)="A class cannot be its own superclass."
		  dmsg.value(70)="Cannot assign a value to this property."
		  dmsg.value(71)="Cannot get this property's value."
		  dmsg.value(72)="The If statement is missing its condition."
		  dmsg.value(73)="The current function must return a value, but this Return statement does not specify any value."
		  dmsg.value(74)="Parameter options are incompatible."
		  dmsg.value(75)="Parameter option was already specified."
		  dmsg.value(76)="A parameter passed by reference cannot have a default value."
		  dmsg.value(77)="A ParamArray cannot have a default value."
		  dmsg.value(78)="An Assigns parameter cannot have a default value."
		  dmsg.value(79)="An Extends parameter cannot have a default value."
		  dmsg.value(80)="Only the first parameter may use the Extends option."
		  dmsg.value(81)="Only the last parameter may use the Assigns option."
		  dmsg.value(82)="An ordinary parameter cannot follow a ParamArray."
		  dmsg.value(83)="Only one parameter may use the Assigns option."
		  dmsg.value(84)="Only one parameter may use the ParamArray option."
		  dmsg.value(85)="A ParamArray cannot have more than one dimension."
		  dmsg.value(86)="The keyword 'Then' is expected after this If statement's condition."
		  dmsg.value(87)="Undefined member identifier."
		  dmsg.value(88)="Constants must be defined with constant values."
		  dmsg.value(89)="Illegal use of the Call keyword."
		  dmsg.value(90)="No cases may follow the Else block."
		  dmsg.value(91)="A computed property can only contain 'Get' and 'Set' blocks."
		  dmsg.value(92)="A computed property getter or setter block ends with the wrong 'end' line. For example, if you start the block with 'Get', it must end with 'End Get'."
		  dmsg.value(93)="Duplicate method definition."
		  dmsg.value(94)="Syntax Error: The library name for this declaration is blank."
		  dmsg.value(95)="This If statement is missing an End If statement."
		  dmsg.value(96)="This Select Case statement is missing an End Select statement."
		  dmsg.value(97)="This For loop is missing its Next statement."
		  dmsg.value(98)="This While loop is missing its Wend statement."
		  dmsg.value(99)="This Try statement is missing an End Try statement."
		  dmsg.value(100)="This Do loop is missing its Loop statement."
		  dmsg.value(101)="Too few parentheses."
		  dmsg.value(102)="Too many parentheses."
		  dmsg.value(103)="There is no block to continue here."
		  dmsg.value(104)="There is no (%1) block to (%2) here."
		  dmsg.value(105)="Shared methods cannot access instance properties."
		  dmsg.value(106)="Instance methods need an object: call this on an instance."
		  dmsg.value(107)="Shared computed property accessors cannot access instance properties."
		  dmsg.value(108)="Shared computed property accessors cannot access instance methods."
		  dmsg.value(109)="The Constructor of this class is protected, and can only be called from within this class."
		  dmsg.value(110)="This string field needs to specify its length."
		  dmsg.value(111)="Structures cannot contain fields of this type."
		  dmsg.value(112)="Syntax Error: Structures cannot contain multidimensional arrays."
		  dmsg.value(113)="Enumerated types can only contain integers."
		  dmsg.value(114)="An enumeration cannot be defined in terms of another enumeration."
		  dmsg.value(115)="This is a constant; its value can't be changed."
		  dmsg.value(116)="A String field must be at least 1 byte long."
		  dmsg.value(117)="The storage size specifier only applies to String fields."
		  dmsg.value(118)="A structure cannot contain itself."
		  dmsg.value(119)="Cannot create an instance of structure with New because it is not a class."
		  dmsg.value(120)="Cannot create an instance of enum with New because it is not a class."
		  dmsg.value(121)="This type is private, and can only be used within its module."
		  dmsg.value(122)="Class members cannot be global."
		  dmsg.value(123)="Module members must be public or private; they cannot be protected."
		  dmsg.value(124)="Members of inner modules cannot be global."
		  dmsg.value(125)="A Dim/Var statement creates only one new object at a time."
		  dmsg.value(126)="A constant was expected here, but this is some other kind of expression."
		  dmsg.value(127)="This module is private, and can only be used within its containing module."
		  dmsg.value(128)="Duplicate property definition."
		  dmsg.value(129)="This datatype cannot be used as an array element."
		  dmsg.value(130)="Delegate parameters cannot be optional."
		  dmsg.value(131)="Delegates cannot use Extends, Assigns, or ParamArray."
		  dmsg.value(132)="The Declare statement is illegal in XojoScript."
		  dmsg.value(133)="It is not legal to dereference a Ptr value in XojoScript."
		  dmsg.value(134)="Delegate creation from Ptr values is not allowed in XojoScript."
		  dmsg.value(135)="Duplicate constant definition."
		  dmsg.value(136)="Ambiguous interface method implementation."
		  dmsg.value(137)="Illegal explicit interface method implementation. The class does not claim to implement this interface."
		  dmsg.value(138)="The interface does not declare this method."
		  dmsg.value(139)="This method contains a #If without a closing #endif statement."
		  dmsg.value(140)="This interface contains a cyclical interface aggregation."
		  dmsg.value(141)="The Extends modifier cannot be used on a class method."
		  dmsg.value(142)="You cannot assign a non-value type to a value."
		  dmsg.value(143)="Duplicate attribute name."
		  dmsg.value(144)="Delegates cannot return structures."
		  dmsg.value(145)="You cannot use AddressOf on this method. Possible causes include using AddressOf on event declarations or soft declares."
		  dmsg.value(146)="You cannot use an Operator_Convert method to perform a convert-to operation on an interface."
		  dmsg.value(147)="Syntax Error: The ElseIf statement is missing its condition."
		  dmsg.value(148)="This type cannot be used as an explicit constant type."
		  dmsg.value(149)="Recursive constant declaration error."
		  dmsg.value(150)="Custom error created using 'Error' pragma."
		  dmsg.value(151)="This is not a local variable or parameter."
		  dmsg.value(152)="The maximum units in last position parameter must be a constant."
		  dmsg.value(153)="The maximum units in last position parameter is out of range."
		  dmsg.value(154)="The StructureAlignment attribute's value must be of the following: 1, 2, 4, 8, 16, 32, 64, or 128."
		  dmsg.value(155)="Pair creation via the ':' operator is not allowed in XojoScript."
		  dmsg.value(156)="Introspection via the GetTypeInfo operator is not allowed in XojoScript."
		  dmsg.value(157)="The For statement is missing its condition."
		  dmsg.value(158)="The While statement is missing its condition."
		  dmsg.value(159)="Unsigned integer used in negative step loops can cause an infinite loop."
		  dmsg.value(160)="Must use Objects with Is."
		  dmsg.value(161)="Only objects can be used with AddHandler and RemoveHandler."
		  dmsg.value(162)="The object you are passing to AddHandler does not have the specified event."
		  dmsg.value(163)="Converting Delegates to Ptrs is not allowed in XojoScript."
		  dmsg.value(164)="WeakAddressOf can only be used on instance methods."
		  dmsg.value(165)="Declares directly into the runtime via Lib '' are no longer allowed."
		  dmsg.value(166)="Objective-C declares must have at least one parameter (the target of the message send)."
		  dmsg.value(167)="This property shadows a property of a different type."
		  dmsg.value(168)="Goto target not found."
		  dmsg.value(169)="#pragma warning' requires a warning message."
		  dmsg.value(170)="#pragma error' requires an error message."
		  dmsg.value(171)="Duplicate label."
		  dmsg.value(172)="Object properties cannot have default values."
		  dmsg.value(173)="Array properties cannot have default values."
		  dmsg.value(174)="For Each loops over iterable objects cannot be used in XojoScript."
		  dmsg.value(175)="This object does not implement the Iterable interface and cannot be used in a For Each loop."
		  dmsg.value(178)="This is a type name, not a variable; values can't be assigned to it."
		  dmsg.value(179)="This is a module, not a variable; values can't be assigned to it."
		  dmsg.value(180)="Can't find a type with this name."
		  dmsg.value(181)="Expected a type name but found %1 instead."
		  dmsg.value(182)="Can't find a type or module with this name."
		  dmsg.value(183)="Expected a type or module name here but found %1 instead."
		  dmsg.value(184)="Extension method %1 requires a conversion from %2 to %3; use CType to explicitly convert first."
		  dmsg.value(185)="Can't find a type with this name. Did you mean %1?"
		  dmsg.value(186)="Undefined operator. Type %1 does not define '%2' with type %3."
		  dmsg.value(187)="Undefined operator. Type %1 does not define '%2'."
		  dmsg.value(188)="Cannot import %1 from %2 because it is Global, not Public."
		  dmsg.value(189)="Cannot import %1 from %2 because it is Private to its container, not Public."
		  dmsg.value(190)="Expected a value of type %1, but found a static namespace reference to %2."
		  dmsg.value(191)="Cannot create an instance of %1 with New because it is not a class."
		  dmsg.value(192)="Cannot create an instance of %1 with New because it is not a class. Did you mean %2?"
		  dmsg.value(193)="%1 is not available."
		  dmsg.value(194)="Too many arguments: got %1, expected only %2."
		  dmsg.value(195)="Too many arguments: got %1, expected no more than %2."
		  dmsg.value(196)="Not enough arguments: missing %3 value for parameter '%4'."
		  dmsg.value(197)="Not enough arguments: got %1, expected %2."
		  dmsg.value(198)="Not enough arguments: got %1, expected at least %2."
		  dmsg.value(199)="Assignment accessor must be invoked by assigning a value."
		  dmsg.value(200)="This method cannot accept an assigned value (it lacks an Assigns parameter)."
		  dmsg.value(201)="Parameter '%1' expects %2, but this is %3."
		  dmsg.value(202)="Expected (%1), but these arguments are (%2)."
		  dmsg.value(203)="ParamArray '%1' expects values of %2, but this is %3."
		  dmsg.value(204)="Instance methods need an object: call this on an instance of %1."
		  dmsg.value(205)="Extension methods need a base expression: call this on a value of %1."
		  dmsg.value(206)="Static reference to instance method: call this on an instance of %1."
		  dmsg.value(207)="Static reference to extension method: call this on a value of %1."
		  dmsg.value(208)="This method extends %1, but the base expression is %2."
		  dmsg.value(209)="Cannot convert from %1 to %2 because %3 is protected."
		  dmsg.value(210)="Fixed-length string fields are no longer supported; use an array of Byte instead."
		  
		  return
		  
		End Sub
	#tag EndMethod

	#tag Method, Flags = &h0
		Sub Constructor(OutputHandler as OutputDelegate)
		  
		  self.script = new XojoScript
		  
		  AddHandler self.script.Input, AddressOf HandleInput
		  AddHandler self.script.Print,  AddressOf HandleOutput
		  AddHandler self.script.CompilerError, AddressOf HandleCompilerError
		  
		  self.Writer = OutputHandler
		  
		  BuildErrorDictionary
		  
		  Return
		  
		  
		End Sub
	#tag EndMethod

	#tag Method, Flags = &h0
		Function HandleCompilerError(x As XojoScript, location As XojoScriptLocation, error As XojoScript.Errors, errorInfo As Dictionary) As Boolean
		  
		  var msgs() as string
		  
		  if self.dmsg = nil then
		    msgs.Add("Line " + str(location.Line) + " column " + str(location.Column)+": Error " + str(error))
		    
		  else
		    msgs.Add("Line " + str(location.Line) + " column " + str(location.Column)+": Error " + self.dmsg.Lookup(error, "Unknown error"))
		    
		  end if
		  
		  for each k as Variant in errorInfo.keys
		    msgs.Add( "Line " + str(location.Line) + " column " + str(location.Column)+": "+ errorInfo.Value(k).StringValue)
		    
		  next
		  
		  for each msg as string in msgs
		    self.LastScriptOutput = msg
		    
		    if self.Writer <> nil then self.Writer.Invoke(msg)
		    
		  next
		  
		  return false
		  
		End Function
	#tag EndMethod

	#tag Method, Flags = &h0
		Function HandleInput(x as XojoScript, m as string) As string
		  
		  return LastScriptInput
		  
		End Function
	#tag EndMethod

	#tag Method, Flags = &h0
		Sub HandleOutput(x as XojoScript, m as string)
		  
		  self.LastScriptOutput = m
		  
		  if self.Writer = nil then return
		  
		  self.Writer.Invoke(m)
		  
		  return
		  
		End Sub
	#tag EndMethod

	#tag DelegateDeclaration, Flags = &h0
		Delegate Sub OutputDelegate(Message as String)
	#tag EndDelegateDeclaration

	#tag Method, Flags = &h0
		Function RunWithInput(InputMessage as string) As string
		   
		  self.LastScriptInput = InputMessage
		  
		  script.Context = new clScriptContextClass
		  
		  if script.Precompile(XojoScript.OptimizationLevels.Low) then
		    Script.run()
		    return LastScriptOutput
		    
		  else
		    return "Compilation error(s)"
		    
		  end if
		   
		End Function
	#tag EndMethod

	#tag Method, Flags = &h0
		Sub SetSource(SourceCode as string)
		  
		  script.Source = SourceCode
		  
		End Sub
	#tag EndMethod


	#tag Property, Flags = &h0
		dmsg As Dictionary
	#tag EndProperty

	#tag Property, Flags = &h0
		LastScriptInput As string
	#tag EndProperty

	#tag Property, Flags = &h0
		LastScriptOutput As string
	#tag EndProperty

	#tag Property, Flags = &h0
		script As XojoScript
	#tag EndProperty

	#tag Property, Flags = &h0
		Writer As OutputDelegate
	#tag EndProperty


	#tag ViewBehavior
		#tag ViewProperty
			Name="Name"
			Visible=true
			Group="ID"
			InitialValue=""
			Type="String"
			EditorType=""
		#tag EndViewProperty
		#tag ViewProperty
			Name="Index"
			Visible=true
			Group="ID"
			InitialValue="-2147483648"
			Type="Integer"
			EditorType=""
		#tag EndViewProperty
		#tag ViewProperty
			Name="Super"
			Visible=true
			Group="ID"
			InitialValue=""
			Type="String"
			EditorType=""
		#tag EndViewProperty
		#tag ViewProperty
			Name="Left"
			Visible=true
			Group="Position"
			InitialValue="0"
			Type="Integer"
			EditorType=""
		#tag EndViewProperty
		#tag ViewProperty
			Name="Top"
			Visible=true
			Group="Position"
			InitialValue="0"
			Type="Integer"
			EditorType=""
		#tag EndViewProperty
		#tag ViewProperty
			Name="script"
			Visible=false
			Group="Behavior"
			InitialValue=""
			Type="Integer"
			EditorType=""
		#tag EndViewProperty
	#tag EndViewBehavior
End Class
#tag EndClass
