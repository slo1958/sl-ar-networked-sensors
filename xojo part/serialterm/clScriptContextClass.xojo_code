#tag Class
Protected Class clScriptContextClass
	#tag Method, Flags = &h0
		Function GetHexasString(Value as UInt64, Length as UInt8) As String
		  
		  var tmp as string = hex(Value)
		  
		  if Length = 0 then return tmp
		  if Length > 16 then return tmp
		  
		  
		  while tmp.Length < Length
		    tmp = "0" + tmp
		    
		  wend
		  
		  if tmp.Length > Length then 
		    tmp =  "*"
		    while tmp.Length < Length
		      tmp = "*" + tmp
		      
		    wend
		    
		  end if
		  
		  return tmp
		  
		End Function
	#tag EndMethod

	#tag Method, Flags = &h0
		Function GetMD5String(s as string) As string
		  Return MD5(s)
		  
		End Function
	#tag EndMethod

	#tag Method, Flags = &h0
		Function SumByteCodeOnByte(source as string) As UInt8
		  var tmp as UInt8
		  
		  for i as integer = 0 to source.bytes
		    tmp = tmp + source.MiddleBytes(i,1).AscByte
		    
		  next
		  
		  return tmp
		  
		End Function
	#tag EndMethod

	#tag Method, Flags = &h0
		Function SumByteCodeOnInt16(source as string) As UInt16
		  var tmp as UInt16
		  
		  for i as integer = 0 to source.bytes
		    tmp = tmp + source.MiddleBytes(i,1).AscByte
		    
		  next
		  
		  return tmp
		  
		End Function
	#tag EndMethod

	#tag Method, Flags = &h0
		Function SumCodePoints(source as string) As UInt64
		  var tmp as UInt64
		  
		  For Each codePoint As UInt32 In source.Codepoints
		    tmp = tmp + codePoint
		    
		  next
		  
		  return tmp
		  
		End Function
	#tag EndMethod


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
	#tag EndViewBehavior
End Class
#tag EndClass
