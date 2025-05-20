#tag Class
Protected Class SerialComm
	#tag Method, Flags = &h0
		Sub Close()
		  
		  if Connection = nil then Return
		  
		  Connection.Reset
		  
		  Connection.Close
		  
		  Connection = nil 
		  
		  Return
		  
		  
		End Sub
	#tag EndMethod

	#tag Method, Flags = &h0
		Function Connected() As Boolean
		  
		  return Connection <> nil
		  
		End Function
	#tag EndMethod

	#tag Method, Flags = &h0
		Sub Constructor(myDevice as SerialDevice)
		  self.BaudRate = SerialConnection.Baud9600
		  self.ByteSize = SerialConnection.Bits8
		  
		  self.Device = myDevice
		  
		  Return
		End Sub
	#tag EndMethod

	#tag Method, Flags = &h0
		Function DeviceName() As string
		  if device = nil then return ""
		  
		  return device.Name
		  
		  
		End Function
	#tag EndMethod

	#tag Method, Flags = &h0
		Shared Function GetDeviceFromName(name as string) As SerialDevice
		  
		  For i As Integer = 0 To SerialDevice.LastIndex
		    if SerialDevice.At(i).Name = name then Return SerialDevice.At(i)
		    
		  Next
		  
		  return nil
		  
		  
		  
		  
		End Function
	#tag EndMethod

	#tag Method, Flags = &h0
		Shared Function GetDeviceList() As string()
		  
		  var list() as string
		  
		  For i As Integer = 0 To SerialDevice.LastIndex
		    List.Add(SerialDevice.At(i).Name)
		    
		  Next
		  
		  return list
		  
		  
		  
		End Function
	#tag EndMethod

	#tag Method, Flags = &h0
		Function Open() As Boolean
		  
		  self.Connection = new SerialConnection()
		  self.Connection.Device = device
		  Self.Connection.Baud = self.BaudRate
		  Self.Connection.Bits = SerialConnection.Bits8
		  
		  try
		    self.Lasterror = ""
		    
		    self.Connection.Connect
		    return True
		    
		  catch e as IOException
		    self.Lasterror = e.Message
		    Return false
		    
		  end try
		  
		End Function
	#tag EndMethod

	#tag Method, Flags = &h0
		Function Read() As string
		  
		  
		  if Connection = nil then return ""
		  
		  try
		    self.Lasterror = ""
		    
		    return Connection.ReadAll
		    
		  Catch e as IOException
		    self.Lasterror = e.Message
		    return ""
		    
		  end try
		  
		End Function
	#tag EndMethod

	#tag Method, Flags = &h0
		Sub SetBaudRate(NewBaudRate as integer)
		  self.BaudRate = NewBaudRate
		  
		  return
		End Sub
	#tag EndMethod

	#tag Method, Flags = &h0
		Sub SetByteSize(NewByteSize as Integer)
		  
		  self.ByteSize = NewByteSize
		  
		  Return
		  
		End Sub
	#tag EndMethod

	#tag Method, Flags = &h0
		Function Write(data as string) As Boolean
		  
		  if Connection = nil then Return false
		  
		  try
		    
		    Connection.Write(data)
		    Connection.Flush
		    return True
		    
		  catch e as IOException
		    self.Lasterror  = e.Message
		    return false
		    
		  end try
		  
		  
		End Function
	#tag EndMethod


	#tag Property, Flags = &h1
		Protected BaudRate As Integer
	#tag EndProperty

	#tag Property, Flags = &h1
		Protected ByteSize As Integer
	#tag EndProperty

	#tag Property, Flags = &h1
		Protected Connection As SerialConnection
	#tag EndProperty

	#tag Property, Flags = &h1
		Protected Device As SerialDevice
	#tag EndProperty

	#tag Property, Flags = &h0
		Lasterror As string
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
			Name="Lasterror"
			Visible=false
			Group="Behavior"
			InitialValue=""
			Type="string"
			EditorType="MultiLineEditor"
		#tag EndViewProperty
	#tag EndViewBehavior
End Class
#tag EndClass
