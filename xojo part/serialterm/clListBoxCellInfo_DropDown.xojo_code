#tag Class
Protected Class clListBoxCellInfo_DropDown
Inherits clListBoxCellInfo
	#tag Method, Flags = &h0
		Sub Constructor(paRow as integer,paColumn as integer,paValue as String,paCanDropDown as Boolean)
		  
		  
		  Super.Constructor(paRow,paColumn,paValue)
		  
		  CanDropDown = paCanDropDown
		  
		  
		End Sub
	#tag EndMethod

	#tag Method, Flags = &h0
		Sub Constructor(paRow as integer,paColumn as integer,paValue as String,paCanDropDown as Boolean,paStringList() as String)
		  
		  Super.Constructor(paRow,paColumn,paValue)
		  
		  if UBound(paStringList) > -1 then
		    FillDropDownList(paStringList)
		    CanDropDown = paCanDropDown
		  else
		    CanDropDown = false
		  end if
		End Sub
	#tag EndMethod

	#tag Method, Flags = &h0
		Sub FillDropDownList(paStringList() as String)
		  
		  dim i as integer
		  
		  redim DropDownList(-1)
		  
		  for  i = 0 to UBound(paStringList)
		    DropDownList.Append(paStringList(i))
		  next
		End Sub
	#tag EndMethod


	#tag Property, Flags = &h0
		CanDropDown As Boolean
	#tag EndProperty

	#tag Property, Flags = &h0
		CellHasChanged As Boolean = False
	#tag EndProperty

	#tag Property, Flags = &h0
		DataFieldId As String
	#tag EndProperty

	#tag Property, Flags = &h0
		DbFieldName As String
	#tag EndProperty

	#tag Property, Flags = &h0
		DropDownButtonX1 As Integer = 0
	#tag EndProperty

	#tag Property, Flags = &h0
		DropDownButtonX2 As Integer = 0
	#tag EndProperty

	#tag Property, Flags = &h0
		DropDownList() As String
	#tag EndProperty

	#tag Property, Flags = &h0
		HasPassedValidation As Boolean = true
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
			Name="CanDropDown"
			Visible=false
			Group="Behavior"
			InitialValue="0"
			Type="Boolean"
			EditorType=""
		#tag EndViewProperty
		#tag ViewProperty
			Name="DropDownButtonX1"
			Visible=false
			Group="Behavior"
			InitialValue="0"
			Type="Integer"
			EditorType=""
		#tag EndViewProperty
		#tag ViewProperty
			Name="DropDownButtonX2"
			Visible=false
			Group="Behavior"
			InitialValue="0"
			Type="Integer"
			EditorType=""
		#tag EndViewProperty
		#tag ViewProperty
			Name="DbFieldName"
			Visible=false
			Group="Behavior"
			InitialValue=""
			Type="String"
			EditorType="MultiLineEditor"
		#tag EndViewProperty
		#tag ViewProperty
			Name="DataFieldId"
			Visible=false
			Group="Behavior"
			InitialValue=""
			Type="String"
			EditorType="MultiLineEditor"
		#tag EndViewProperty
		#tag ViewProperty
			Name="HasPassedValidation"
			Visible=false
			Group="Behavior"
			InitialValue="true"
			Type="Boolean"
			EditorType=""
		#tag EndViewProperty
		#tag ViewProperty
			Name="CellHasChanged"
			Visible=false
			Group="Behavior"
			InitialValue="False"
			Type="Boolean"
			EditorType=""
		#tag EndViewProperty
	#tag EndViewBehavior
End Class
#tag EndClass
