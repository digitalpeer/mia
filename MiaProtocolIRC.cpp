

/*
NOT IMPLIMENTED YET    
THis is some code from a VB client i wrote a long, long time ago
*/

//MiaIRC::connect()
//{
	//theSocket.send("User " + email + " " + tcp.LocalHostName + " " + tcp.RemoteHost + " :" + RealName & "\r\n");
    //theSocket.send("NICK " + NickName + "\r\n");
//}

/*
Public Sub command(Username As String, command As String, target As String, parms As String)
    Dim i As Integer
    Dim x As Integer
    Dim found As Boolean
    
    'chop off the ":" in front of all parameters
    If Left(parms, 1) = ":" Then
        parms = Trim(Mid(parms, 2))
    End If
    Form1.stat.Text = Form1.stat.Text & command & " " & parms & vbCrLf & "TARGET: " & target & vbCrLf
    
    'break down usrename
    Dim UserEmail
    For i = 1 To Len(Username)
        If Mid(Username, i, 1) = "!" Then
            UserEmail = Mid(Username, i + 1)
            Username = Mid(Username, 1, i - 1)
            If Left(Username, 1) = ":" Then
                Username = Mid(Username, 2)
            End If
        End If
    Next i
    
    
    'this SELECT CASE is for anything that's not a 'command'
    Select Case UCase(Username)
        Case "PING"
            Form1.tcp.SendData "PONG " & parms & vbCrLf
            'frmStatus.txtStatus.SelColor = RGB(0, 140, 0)
            Form1.stat.Text = Form1.stat.Text & "*** PONG " & parms & vbCrLf
            'status window shows server name
            'frmStatus.Caption = "Cabral Status: " & parms
            'mdiMain shows [server name]
            Form1.Caption = "Cabral IRC [" & parms & "]"
            'frmStatus.txtStatus.SelColor = vbBlack
    End Select
    
    Select Case UCase(command)
        Case "JOIN"
        '    For i = 1 To 10
                'if you join channel then load channel window
'                If ChannelName(i) = "" Then
 '                   If LCase(Username) = LCase(NickName) Then
  '                      Load Channel(i)
   '                     ChannelName(i) = LCase(parms)
    '                    Channel(i).Caption = parms
     '                   Exit For
      '              End If
       '         End If
                'other users join channel
                'update nick list box
         '       If LCase(ChannelName(i)) = LCase(parms) Then
          '          Channel(i).lstNames.AddItem Username
           '         'show in channel that user joined channel
            '        Channel(i).txtText.SelColor = RGB(0, 140, 0)
             '       Channel(i).txtText.SelText = "*** " & Username & " has joined " & parms & vbCrLf
              '      Channel(i).txtText.SelColor = vbBlack
              '  End If
            'Next i
        Case "PART"
    '        For i = 1 To 10
                'if you leave then unload channel window
     '           If ChannelName(i) = LCase(parms) Then
      '              If LCase(Username) = LCase(NickName) Then
       '                 Unload Channel(i)
        '                ChannelName(i) = ""
         '               Exit For
          '          End If
           '     End If
                'other users leave channel
                'update nick list box
    '            If LCase(ChannelName(i)) = LCase(parms) And parms <> "" Then
   '                 'cycle through names and remove if found
     '               For x = 0 To Channel(i).lstNames.ListCount - 1
      '                  If Channel(i).lstNames.ListIndex Then
       '                     If LCase(Channel(i).lstNames.List(x)) = LCase(Username) Or LCase(Channel(i).lstNames.List(x)) = LCase("@" & Username) Then
        '                        Channel(i).lstNames.RemoveItem (x)
         '                       'show in channel that user left channel
          '                      Channel(i).txtText.SelColor = RGB(0, 140, 0)
           '                     Channel(i).txtText.SelText = "*** " & Username & " has left " & parms & vbCrLf
            '                    Channel(i).txtText.SelColor = vbBlack
                                'Exit For
             '               End If
              '          End If
               '     Next x
                    
    '            End If
     '       Next i
        Case "PRIVMSG"
        'MsgBox "you got the message :" & parms & ":"
        'MsgBox target
        'If Username <> "digitalpeer100" Then
        If target = "digitalpeer100" Then target = Username
        If parms = "you are the shit" Then
        Form1.tcp.SendData "PRIVMSG " & target & " :your my bitch" & vbCrLf
        ElseIf parms = "what time is it?" Then
        Form1.tcp.SendData "PRIVMSG " & target & " :" & Time & vbCrLf
        ElseIf parms = "who is your master?" Then
        Form1.tcp.SendData "PRIVMSG " & target & " :the fearless digitalpeer" & vbCrLf
        ElseIf parms = "?version?" Then
        Form1.tcp.SendData "PRIVMSG " & target & " :Version 1.0 of DPBOT" & vbCrLf
        ElseIf parms = "fuck you" Then
        Form1.tcp.SendData "PRIVMSG " & target & " :WHORE" & vbCrLf
        Else
        'MsgBox target
        
       
        
        'Form1.tcp.SendData "PRIVMSG " & target & " :I don't understand this: " & parms & vbCrLf
        End If
        'End If
        
        
      '      If Left(target, 1) = "#" Then
       '         For i = 1 To 10
      '              If ChannelName(i) = LCase(target) Then
                        'if it's a channel action
       '                 If LCase(Left(parms, 7)) = LCase(".ACTION") Then
        '                    Channel(i).txtText.SelColor = RGB(140, 0, 140)
         '                   Channel(i).txtText.SelText = "* "
          '                  Channel(i).txtText.SelBold = True
           '                 Channel(i).txtText.SelText = Username
            '                Channel(i).txtText.SelBold = False
             '               Channel(i).txtText.SelText = " " & Mid(parms, 8) & vbCrLf
              '              Channel(i).txtText.SelColor = vbBlack
               '         Else
                '            Channel(i).txtText.SelText = "<"
                 '           Channel(i).txtText.SelBold = True
                  '          Channel(i).txtText.SelText = Username
                   '         Channel(i).txtText.SelBold = False
                    '        Channel(i).txtText.SelText = "> " & parms & vbCrLf
                     '   End If
        '            Else
                        'if exited channel before PART msg then show channel text in status
                        'bottom line echos 10 times in status (fix)
                        'Form1.stat.Text = Form1.stat.Text  & target & ": <" & Username & "> " & parms & vbCrLf
         '           End If
           '     Next i
          '  Else
            '    found = False
                
             '   For i = 1 To 100
              '      If LCase(Username) = LCase(QueryName(i)) Then
               '         found = True
                '        Exit For
                 '   End If
               ' Next i
    '            If found = False Then
     '               For i = 1 To 100
      '                  If QueryName(i) = "" Then
       '                     'load query window
        '                    Load Query(i)
         '                   Query(i).Caption = Username
          '                  QueryName(i) = Username
           '                 Exit For
            '            End If
             '       Next i
              '  End If
                
               ' For i = 1 To 100
                '    If LCase(QueryName(i)) = LCase(Username) Then
                 '       Query(i).txtQuery.SelText = "<"
                  '      Query(i).txtQuery.SelBold = True
                   '     Query(i).txtQuery.SelColor = vbRed
                    ''    Query(i).txtQuery.SelText = Username
                      '  Query(i).txtQuery.SelBold = False
                       ' Query(i).txtQuery.SelColor = vbBlack
                        'Query(i).txtQuery.SelText = "> " & parms & vbCrLf
 '                   End If
  '              Next i
   '         End If
        Case "NICK"
            'Update your nickname variable
            If LCase(Username) = LCase(NickName) Then
                NickName = parms
            End If
        Case "NOTICE"
            'channel notice
    '        If Left(target, 1) = "#" Then
     '           For i = 1 To 10
      '              'cycle through channel names and if found a match then
       '             'writing to channel window
        '            If LCase(target) = LCase(ChannelName(i)) Then
         '               Channel(i).txtText.SelColor = RGB(140, 0, 0)
          '              Channel(i).txtText.SelText = target
           '             Channel(i).txtText.SelColor = vbBlack
            '            Channel(i).txtText.SelText = ": <"
             '           Channel(i).txtText.SelBold = True
              '          Channel(i).txtText.SelText = Username
               '         Channel(i).txtText.SelBold = False
                '        Channel(i).txtText.SelText = "> " & parms & vbCrLf
                 '   Else
                  '      'show channel NOTICE to status window
                   '
 '                   End If
  '              Next i
   '         Else
                'personal NOTICE to you
                'query window for username not found yet
    '            found = False
     '
      '          'loop to find an already open query window
       '         For i = 1 To 100
        '            If LCase(QueryName(i)) = LCase(Username) Then
         '               found = True
          '          End If
           '     Next i
            '
             '   'create query window if not already loaded
  '              If found = False Then
   '                 For i = 1 To 100
    '                    If QueryName(i) = "" Then
     '                       'load query window
      '                      Load Query(i)
       '                     Query(i).Caption = Username
        '                    QueryName(i) = Username
         '                   Exit For
          '              End If
           '         Next i
            '    End If
                'finally show NOTICE in query window
'                For i = 1 To 100
 '                   If LCase(QueryName(i)) = LCase(Username) Then
  '                      Query(i).txtQuery.SelColor = RGB(140, 0, 0)
   '                     Query(i).txtQuery.SelBold = True
    '                    Query(i).txtQuery.SelText = "NOTICE"
     '                   Query(i).txtQuery.SelBold = False
      '                  Query(i).txtQuery.SelColor = vbBlack
       '                 Query(i).txtQuery.SelText = ": " & parms & vbCrLf
        '            End If
         ''       Next i
           ' End If
        Case "QUIT"
            'cycle through each window since the QUIT message
            'tells you no channel or anything
  '          For i = 1 To 10
   '             'if channel exsists (should have name)
    '            If ChannelName(i) <> "" Then
     '               'cycle through each listbox on each channel window
      '              For x = 0 To Channel(i).lstNames.ListCount - 1
       '                 'if QUIT name matches lstnames(name) then remove
        '                If LCase(Channel(i).lstNames.List(x)) = LCase(Username) Or LCase(Channel(i).lstNames.List(x)) = LCase("@" & Username) Then
         '                   'remove from list box for certain window
          '                  Channel(i).lstNames.RemoveItem (x)
           '                 'Display quit in channel
            '                Channel(i).txtText.SelColor = RGB(0, 0, 140)
             '               Channel(i).txtText.SelText = "*** " & Username & " has QUIT (" & parms & ")" & vbCrLf
              '              Channel(i).txtText.SelColor = vbBlack
               '         End If
                '    Next x
         '       End If
        '    Next i
    End Select
End Sub
*/
