
package calculadorip;

import java.awt.Color;
import javax.swing.JOptionPane;
import javax.swing.table.DefaultTableModel;


public class Calc extends javax.swing.JFrame {

    
    public Calc() {
        initComponents();

        //jTable1.setModel(makeModel(tablet,ips.length,ips));
        //jTable2.setModel(makeModel(tablet2,ips.length,ips));
        
    }
   
    Validation validar=new Validation();
    //DbTools db = new DbTools();
    String[] tablet1  = {"Subredes"};
    String[] tablet2  = {"Host"};
    int prefix=0;
    int snet=0;
    int hst=0;
    int clas;
    String SelectedItem;

    public static DefaultTableModel makeModel(String[] e , String [] columns, int per)
    {
        DefaultTableModel modelo = new DefaultTableModel();

        for(int i = 0;i<columns.length;i++)
        {
            modelo.addColumn(columns[i]);
        }

        Object [] row = new Object[columns.length];
        //String []u={"22","33"};
        

        Object[] linea = new Object[1]; 
        int hu;
        for(hu=0;hu<per;hu++)
        {
         linea[0] = e[hu]; 
         modelo.addRow(linea);
         
        }
         
 

        return modelo;
    }
    
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        buttonGroup1 = new javax.swing.ButtonGroup();
        jLabel2 = new javax.swing.JLabel();
        jTextField1 = new javax.swing.JTextField();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        jLabel5 = new javax.swing.JLabel();
        jLabel6 = new javax.swing.JLabel();
        jLabel7 = new javax.swing.JLabel();
        jComboBox1 = new javax.swing.JComboBox();
        jLabel8 = new javax.swing.JLabel();
        jLabel9 = new javax.swing.JLabel();
        jLabel10 = new javax.swing.JLabel();
        jTextField2 = new javax.swing.JTextField();
        jLabel11 = new javax.swing.JLabel();
        jLabel12 = new javax.swing.JLabel();
        jScrollPane1 = new javax.swing.JScrollPane();
        jTable1 = new javax.swing.JTable();
        jLabel13 = new javax.swing.JLabel();
        jScrollPane2 = new javax.swing.JScrollPane();
        jTable2 = new javax.swing.JTable();
        jLabel14 = new javax.swing.JLabel();
        jLabel15 = new javax.swing.JLabel();
        jButton1 = new javax.swing.JButton();
        jLabel18 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowOpened(java.awt.event.WindowEvent evt) {
                formWindowOpened(evt);
            }
        });

        jLabel2.setText("Ingrese direccion IP:");

        jTextField1.setFocusCycleRoot(true);
        jTextField1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTextField1ActionPerformed(evt);
            }
        });
        jTextField1.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyReleased(java.awt.event.KeyEvent evt) {
                jTextField1KeyReleased(evt);
            }
        });

        jLabel3.setForeground(new java.awt.Color(51, 153, 255));

        jLabel4.setText("Subredes");

        jLabel5.setText("Host");

        jLabel6.setText("Prefijo");

        jLabel7.setFont(new java.awt.Font("Tahoma", 1, 11));
        jLabel7.setForeground(new java.awt.Color(0, 0, 102));
        jLabel7.setText("Opciones:");

        jComboBox1.setModel(new javax.swing.DefaultComboBoxModel(new String[] { " ", "Subredes", "Host", "Prefijo" }));
        jComboBox1.setEnabled(false);
        jComboBox1.setFocusable(false);
        jComboBox1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jComboBox1ActionPerformed(evt);
            }
        });

        jLabel8.setForeground(new java.awt.Color(102, 102, 102));
        jLabel8.setText(" ");

        jLabel9.setForeground(new java.awt.Color(102, 102, 102));
        jLabel9.setText(" ");

        jLabel10.setForeground(new java.awt.Color(102, 102, 102));
        jLabel10.setText(" ");

        jTextField2.setEnabled(false);
        jTextField2.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyReleased(java.awt.event.KeyEvent evt) {
                jTextField2KeyReleased(evt);
            }
        });

        jLabel11.setForeground(new java.awt.Color(255, 102, 102));
        jLabel11.setText("Clase: ");

        jLabel12.setForeground(new java.awt.Color(102, 102, 102));
        jLabel12.setText(" ");

        jTable1.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null}
            },
            new String [] {
                "Title 1", "Title 2", "Title 3", "Title 4"
            }
        ));
        jTable1.setEnabled(false);
        jTable1.setOpaque(false);
        jTable1.setSurrendersFocusOnKeystroke(true);
        jTable1.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jTable1MouseClicked(evt);
            }
        });
        jScrollPane1.setViewportView(jTable1);

        jLabel13.setText("Lista de Subredes");

        jTable2.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null}
            },
            new String [] {
                "Title 1", "Title 2", "Title 3", "Title 4"
            }
        ));
        jTable2.setEnabled(false);
        jScrollPane2.setViewportView(jTable2);

        jLabel14.setText("Lista de Host");

        jLabel15.setForeground(new java.awt.Color(255, 0, 0));
        jLabel15.setText(" ");

        jButton1.setText("Calcular");
        jButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton1ActionPerformed(evt);
            }
        });

        jLabel18.setFont(new java.awt.Font("Lucida Fax", 1, 24)); // NOI18N
        jLabel18.setForeground(new java.awt.Color(204, 0, 51));
        jLabel18.setText("CALCULADORA IP");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(36, 36, 36)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jLabel4)
                            .addComponent(jLabel5)
                            .addComponent(jLabel6))
                        .addGap(53, 53, 53)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(jLabel9, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(jLabel8, javax.swing.GroupLayout.DEFAULT_SIZE, 130, Short.MAX_VALUE)
                            .addComponent(jLabel10, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(27, 27, 27)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                            .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                                .addComponent(jLabel2)
                                .addGap(18, 18, 18)
                                .addComponent(jTextField1, javax.swing.GroupLayout.PREFERRED_SIZE, 212, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addComponent(jLabel3, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                                .addComponent(jLabel7)
                                .addGap(53, 53, 53)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(jLabel13)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED))
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(jComboBox1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addGap(33, 33, 33)
                                        .addComponent(jTextField2)))))
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(jLabel14)
                                .addGap(45, 45, 45))
                            .addGroup(layout.createSequentialGroup()
                                .addGap(18, 18, 18)
                                .addComponent(jButton1)
                                .addGap(32, 32, 32)
                                .addComponent(jLabel11)
                                .addGap(31, 31, 31)
                                .addComponent(jLabel12, javax.swing.GroupLayout.PREFERRED_SIZE, 64, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jLabel15, javax.swing.GroupLayout.PREFERRED_SIZE, 135, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(80, 80, 80))))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addGap(19, 19, 19)
                        .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 291, Short.MAX_VALUE)
                        .addGap(28, 28, 28)
                        .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 303, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(167, 167, 167)
                        .addComponent(jLabel18)))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(35, 35, 35)
                .addComponent(jLabel18)
                .addGap(10, 10, 10)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(38, 38, 38)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(jLabel2)
                            .addComponent(jTextField1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(jLabel3, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(30, 30, 30)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(jLabel7)
                            .addComponent(jComboBox1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jTextField2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jLabel15))
                        .addGap(18, 18, 18)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(jLabel4)
                            .addComponent(jLabel8))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(jLabel5)
                            .addComponent(jLabel9))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(jLabel6)
                            .addComponent(jLabel10)))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(39, 39, 39)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(jLabel11)
                            .addComponent(jLabel12)
                            .addComponent(jButton1))))
                .addGap(27, 27, 27)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel14)
                    .addComponent(jLabel13))
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 287, Short.MAX_VALUE)
                    .addComponent(jScrollPane2, javax.swing.GroupLayout.DEFAULT_SIZE, 287, Short.MAX_VALUE))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

private void jTextField1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTextField1ActionPerformed
// TODO add your handling code here:
}//GEN-LAST:event_jTextField1ActionPerformed

private void jComboBox1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jComboBox1ActionPerformed
String op=(String) jComboBox1.getSelectedItem();
    
    if(op.equals("Host"))
    {   
        jTextField2.setEnabled(true);
        
    }
    else if(op.equals("Subredes"))
    {   
        jTextField2.setEnabled(true);  
       
    }
    else   if(op.equals("Prefijo"))
    {   jTextField2.setEnabled(true); 
        
    }
   // TODO add your handling code here:
}//GEN-LAST:event_jComboBox1ActionPerformed

private void jTextField1KeyReleased(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_jTextField1KeyReleased
        String ip=jTextField1.getText();
        System.out.println(ip);
        if(validar.isIP(ip)==false || validar.checkLenght(ip, '<', 15) == false)
        {
            jTextField1.setBackground(new Color(255,98,98));
            jComboBox1.setEnabled(false);
            jButton1.setEnabled(false);
        }
        else
        {
            jTextField1.setBackground(Color.white);
            
            jButton1.setEnabled(true);
        }
        jLabel3.setText(" ");
        jLabel12.setText(" ");
        jLabel9.setText(" ");
        jLabel10.setText(" ");
        jLabel8.setText(" ");
        jComboBox1.setEnabled(false);
        jComboBox1.setSelectedItem(" ");
        jTextField2.setText("");
        jTextField2.setEnabled(false);
        
        String []nic =new String[1] ;
        nic[0]=" ";
        
            jTable1.setModel(makeModel(nic, tablet1,1));
        
        String[] nic2=new String [84000];
        nic2[0]=" ";
        
        
            jTable2.setModel(makeModel(nic2, tablet2,1));
        
        /*String sq = "delete from subred";
        try {
            ResultSet consulta = db.consulta('U', sq);
        } catch (SQLException ex) {
            Logger.getLogger(Calc.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        String sql = "SELECT sub FROM subred ";
        try {
            jTable1.setModel(makeModel(db.consulta('Q', sql), tablet1));
        } catch (SQLException ex)
        {
            ex.printStackTrace();
        }*/
}//GEN-LAST:event_jTextField1KeyReleased

private void jTextField2KeyReleased(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_jTextField2KeyReleased
        
    String s=jTextField2.getText();  
    int n;
    String op=(String)jComboBox1.getSelectedItem();
    System.out.println(op);
    if(validar.isInt(s)==false )
        {
            
            jTextField2.setBackground(new Color(255,98,98));
            jLabel9.setText(" ");
            jLabel10.setText(" ");
            jLabel8.setText(" ");
            
            jLabel15.setText(" ");
            //jComboBox1.setEnabled(false);
            //jButton1.setEnabled(false);
        }
        else
        {
            n=Integer.parseInt(s); 
                if( op.equals("Subredes"))
                {
                     if(!valsubredes())
                     {
                         jLabel9.setText(" ");
                        jLabel10.setText(" ");
                        jLabel8.setText(" ");
                        jTextField2.setBackground(new Color(255,98,98));
                        
                     }
                        
                     else
                     {
                        jTextField2.setBackground(Color.white);
                        calcxsub();
                        String pre1=jLabel10.getText();
                        String pre2=jLabel8.getText();
                        String pre3=jLabel9.getText();
                        prefix=Integer.parseInt(pre1);
                        snet=Integer.parseInt(pre2);
                        hst=Integer.parseInt(pre3);
                  
                        tsub();
                     }
                    
                }
                
                if( op.equals("Host"))
                {
                    
                    if(!valhost())
                     {
                        jTextField2.setBackground(new Color(255,98,98));
                        jLabel9.setText(" ");
                        jLabel10.setText(" ");
                        jLabel8.setText(" ");
                     }
                        
                     else
                     {
                        jTextField2.setBackground(Color.white);
                        calcxhost();
                        String pre1=jLabel10.getText();
                        String pre2=jLabel8.getText();
                        String pre3=jLabel9.getText();
                        prefix=Integer.parseInt(pre1);
                        snet=Integer.parseInt(pre2);
                        hst=Integer.parseInt(pre3);
                  
                        tsub();
                     }
                }
                
                if( op.equals("Prefijo"))
                {
                   if(!valprefijo())
                     {
                        jTextField2.setBackground(new Color(255,98,98));
                        jLabel9.setText(" ");
                        jLabel10.setText(" ");
                        jLabel8.setText(" ");
                     }
                        
                     else
                     {
                        jTextField2.setBackground(Color.white);
                        calcxprefijo();
                        String pre1=jLabel10.getText();
                        String pre2=jLabel8.getText();
                        String pre3=jLabel9.getText();
                        prefix=Integer.parseInt(pre1);
                        snet=Integer.parseInt(pre2);
                        hst=Integer.parseInt(pre3);
                  
                        tsub();
                    
                        
                        
                        /*String sql = "SELECT sub FROM subred ";
                try {
                    jTable1.setModel(makeModel(db.consulta('Q', sql), tablet1));
                } catch (SQLException ex)
                {
                    ex.printStackTrace();
                }*/ 
                     }
            }
            
               
        }// TODO add your handling code here:
}//GEN-LAST:event_jTextField2KeyReleased

private void formWindowOpened(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowOpened
   /* String sq = "delete from subred";
        try {
            ResultSet consulta = db.consulta('U', sq);
        } catch (SQLException ex) {
            Logger.getLogger(Calc.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        String sq3 = "delete from host";
        try {
            ResultSet consulta = db.consulta('U', sq3);
        } catch (SQLException ex) {
            Logger.getLogger(Calc.class.getName()).log(Level.SEVERE, null, ex);
        }*/
        String[] nic=new String [84000];
        nic[0]=" ";
        
        
            jTable1.setModel(makeModel(nic, tablet1,1));
            
        String[] nic2=new String [84000];
        nic2[0]=" ";
        
        
            jTable2.setModel(makeModel(nic2, tablet2,1));
        /*
        String sql = "SELECT sub FROM subred ";
            try {
                jTable1.setModel(makeModel(db.consulta('Q', sql), tablet1));
            } catch (SQLException ex)
            {
                ex.printStackTrace();
            }
            String sql2 = "SELECT host FROM host";
            try {
                jTable2.setModel(makeModel(db.consulta('Q', sql2), tablet2));
            } catch (SQLException ex)
            {
                ex.printStackTrace();
            }*/
        
}//GEN-LAST:event_formWindowOpened

private void jTable1MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jTable1MouseClicked
int columna=3;
        int fila=0;
        columna=0;
        fila = jTable1.rowAtPoint(evt.getPoint());
        Object electedItem = jTable1.getValueAt(fila,columna);  
        SelectedItem = electedItem.toString();
        String[] mete=new String [84000000];
        int per=0;
        int o;
         String ss;
         int j;
         int a = 0,b = 0,c = 0,d;
         int nums=0, pto=0;
                    for(o=0;o< SelectedItem.length();o++)
                    {
                        if(SelectedItem.charAt(o) == '.')
                        {
                            pto++;
                            System.out.println(nums);
                            ss=SelectedItem.substring(o-nums, o);
                            nums=0;
                            j=Integer.parseInt(ss);
                            //System.out.println(j);
                            switch(pto)
                            {
                                case 1:
                                    a=j;
                                break;
                                    
                                case 2:
                                    b=j;
                                break;
                                
                                case 3:
                                    c=j;
                                break;
                                    
                                case 4:
                                    d=j;
                                break;    
                            
                            }
                        }
                        else
                        {
                            nums++;
                        }
                    }  
                    String cuatro;
                    cuatro=SelectedItem.substring(SelectedItem.lastIndexOf(".")+1, SelectedItem.length());
                    d=Integer.parseInt(cuatro);
                    System.out.println("elem "+ a +"."+b+"."+c+"."+d);
                    //System.out.println();
                    
                int bits=0;
                    
                switch(clas){
                    
                    case 1:
                        //System.out.println("Hola1");
                        bits=prefix-8;
                        
                        if(bits>0 && bits<9)
                        {
                            int potencia=8-bits;
                            int n;
                            System.out.println(snet);
                            for (n=0;n<(int)Math.pow(2, potencia);n++){
                                
                                
                                for(c=0;c<256;c++)
                                {
                                for(d=1;d<256;d++)
                                {
                                //System.out.println(b);
                                mete[per]=String.valueOf(a)+"."+String.valueOf(b)+"."+String.valueOf(c)+"."+String.valueOf(d);
                                System.out.println(mete[per]);
                                per++;
                                /*String sq = "insert into subred values('"+mete+"')";
                                ResultSet consulta = db.consulta('U', sq);*/
                                jTable2.setModel(makeModel(mete, tablet2,per));
                                }
                               
                                }
                                b++;
        
                            }
                               
                        }
                        if(bits>=9 && bits<17)
                        {
                            int potencia=16-bits;
                            int n;
                            //System.out.println(snet);
                            for (n=0;n<(int)Math.pow(2, potencia);n++){
                                
                                
                                for(d=1;d<256;d++)
                                {
                                //System.out.println(b);
                                mete[per]=String.valueOf(a)+"."+String.valueOf(b)+"."+String.valueOf(c)+"."+String.valueOf(d);
                                System.out.println(mete[per]);
                                per++;
                                /*String sq = "insert into subred values('"+mete+"')";
                                ResultSet consulta = db.consulta('U', sq);*/
                                jTable2.setModel(makeModel(mete, tablet2,per));
                                }
                                c++;
        
                            }
                        }
                        
                        if(bits>=17 && bits<25)
                        {
                            
                            int potencia=24-bits;
                            int n=0,r=0,lim;
                            int d2=d;
                            
                                                                                       
                                
                            for (n=0;n<hst;n++){
                                d2++;
                                //System.out.println(d);
                                mete[per]=String.valueOf(a)+"."+String.valueOf(b)+"."+String.valueOf(c)+"."+String.valueOf(d2);
                                System.out.println(mete[per]);
                                per++;
                                
                                /*String sq = "insert into subred values('"+mete+"')";
                                ResultSet consulta = db.consulta('U', sq);*/
                                
                            }
                            jTable2.setModel(makeModel(mete, tablet2,per));
                        }
                        
                    break;
                    case 2:
                        //System.out.println("Hola2");
                        bits=prefix-16;
                        
                        
                                            
                        if(bits>0 && bits<9)
                        {
                            int potencia=8-bits;
                            int n;
                            System.out.println(snet);
                            for (n=0;n<(int)Math.pow(2, potencia);n++){
                                
                                
                                for(d=1;d<256;d++)
                                {
                                //System.out.println(b);
                                mete[per]=String.valueOf(a)+"."+String.valueOf(b)+"."+String.valueOf(c)+"."+String.valueOf(d);
                                System.out.println(mete[per]);
                                per++;
                                /*String sq = "insert into subred values('"+mete+"')";
                                ResultSet consulta = db.consulta('U', sq);*/
                                jTable2.setModel(makeModel(mete, tablet2,per));
                                }
                                c++;
        
                            }
                               
                        }
                        if(bits>=9 && bits<17)
                        {
                            int potencia=16-bits;
                            int n=0,r=0,lim;
                            int d2=d;
                            
                                                                                       
                                
                            for (n=0;n<hst;n++){
                                d2++;
                                //System.out.println(d);
                                mete[per]=String.valueOf(a)+"."+String.valueOf(b)+"."+String.valueOf(c)+"."+String.valueOf(d2);
                                System.out.println(mete[per]);
                                per++;
                                
                                /*String sq = "insert into subred values('"+mete+"')";
                                ResultSet consulta = db.consulta('U', sq);*/
                                
                            }
                                                       
                            }
                            jTable2.setModel(makeModel(mete, tablet2,per));
                        
                                             
                        
                    break;
                    case 3:
                        
                        bits=prefix-24;
                        
                        if(bits>0 && bits<9)
                        {
                            //System.out.println("Hola");
                            int n;
                            //System.out.println(snet);
                            for (n=0;n<hst;n++){
                                d++;
                                //System.out.println(b);
                                mete[per]=String.valueOf(a)+"."+String.valueOf(b)+"."+String.valueOf(c)+"."+String.valueOf(d);
                                System.out.println(mete[per]);
                                per++;
                                /*String sq = "insert into subred values('"+mete+"')";
                                ResultSet consulta = db.consulta('U', sq);*/
                                jTable2.setModel(makeModel(mete, tablet2,per));
        
                            }
                               
                        }
                        
                    break;
                } 

        
        // TODO add your handling code here:
}//GEN-LAST:event_jTable1MouseClicked

private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton1ActionPerformed
  String ip=jTextField1.getText();
           String oct1 = null;
           int pto;
           pto=ip.indexOf(".");
           oct1=ip.substring(0, pto);
           //System.out.println(oct1);
           int oct;
           oct=Integer.parseInt(oct1);
           //System.out.println(oct);

           //

           int o;
         String ss;
         String s=ip;
         int j;
         int a = 0,b = 0,c = 0,d;
         int nums=0, pto2=0;
                    for(o=0;o< s.length();o++)
                    {
                        if(s.charAt(o) == '.')
                        {
                            pto2++;
                            //System.out.println(nums);
                            ss=s.substring(o-nums, o);
                            nums=0;
                            j=Integer.parseInt(ss);
                            //System.out.println(j);
                            switch(pto2)
                            {
                                case 1:
                                    a=j;
                                break;

                                case 2:
                                    b=j;
                                break;

                                case 3:
                                    c=j;
                                break;

                                case 4:
                                    d=j;
                                break;

                            }
                        }
                        else
                        {
                            nums++;
                        }
                    }
                    String cuatro;
                    cuatro=s.substring(s.lastIndexOf(".")+1, s.length());
                    d=Integer.parseInt(cuatro);
                    System.out.println("elem "+ a +"."+b+"."+c+"."+d);
           //
                    int v=0;

                    if(a==10)
                    {
                        v=0;
                    }
                    else
                    {
                        if(a==172)
                        {
                            if(b>=16 && b<31)
                            {
                                System.out.println("No v");
                               v=0;
                            }
                            else
                            {
                                 System.out.println("Si v");
                                v=1;
                            }
                        }
                        else
                        {
                            if(a==192)

                        {
                            if(b==168)
                            {
                                v=0;
                            }
                            else
                            {
                                v=1;
                            }
                        }
                        else
                        {
                            v=1;
                        }
                        }
                    }





              System.out.println(v);
           if(v==1)
          {
           }

        else
           {
               JOptionPane.showMessageDialog(this,"Dirección Privada" );
           }

           if(oct>=0 && oct <=127)
           {
               if(ip.equals("0.0.0.0"))
               {
                   jLabel3.setText("No se puede procesar");
               }
               else{
               jLabel12.setText("A");
               jComboBox1.setEnabled(true);
               jLabel3.setText(" ");
               clas=1;
               }
           }
          if(oct==127)
          {
            jLabel3.setText("reservado 127 para operaciones locales");

        }
           if(oct>127 && oct <=191)
           {
               jLabel12.setText("B");
               jComboBox1.setEnabled(true);
               jLabel3.setText(" ");
               clas=2;
           }

           if(oct>191 && oct <=223)
           {
               jLabel12.setText("C");
               jComboBox1.setEnabled(true);
               jLabel3.setText(" ");
               clas=3;
           }
           if(oct>223 && oct <=239)
           {
               jLabel12.setText("D");
               jLabel3.setText("Grupo Multicast");
               //jComboBox1.setEnabled(true);
           }
           if(oct>239 && oct <=255)
           {
               if(ip.equals("255.255.255.255"))
               {
                   jLabel3.setText("Dirección de Difusión");
               }
               else{
               jLabel12.setText("E");
               jLabel3.setText("Reservado para uso Futuro");
               }
               //jComboBox1.setEnabled(true);
           }
}//GEN-LAST:event_jButton1ActionPerformed

    public static void main(String args[]) {
       
        java.awt.EventQueue.invokeLater(new Runnable() {

            @Override
            public void run() {
                new Calc().setVisible(true);
            }
        });
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.ButtonGroup buttonGroup1;
    private javax.swing.JButton jButton1;
    private javax.swing.JComboBox jComboBox1;
    private javax.swing.JLabel jLabel10;
    private javax.swing.JLabel jLabel11;
    private javax.swing.JLabel jLabel12;
    private javax.swing.JLabel jLabel13;
    private javax.swing.JLabel jLabel14;
    private javax.swing.JLabel jLabel15;
    private javax.swing.JLabel jLabel18;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JLabel jLabel8;
    private javax.swing.JLabel jLabel9;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JTable jTable1;
    private javax.swing.JTable jTable2;
    private javax.swing.JTextField jTextField1;
    private javax.swing.JTextField jTextField2;
    // End of variables declaration//GEN-END:variables

     private boolean valsubredes() 
     {
        boolean t = false;
         String ip=jTextField1.getText();
        String snet2=jTextField2.getText();
           String oct1 = null;
           int pto;
           pto=ip.indexOf(".");
           oct1=ip.substring(0, pto);
           
           int oct;
           oct=Integer.parseInt(oct1);
           int sn;
           sn=Integer.parseInt(snet2);
           int ns = 0;
           
           
        if(oct>0 && oct <=127)
           {
               
               ns=(int)(Math.pow(2,22))-2;
               
               if(sn<=ns)
               {
                   
                   t= true;
                   jLabel15.setText(" ");
               }
               else 
               {
                   if(sn>=ns && sn<((int)(Math.pow(2,32))-2))
                       jLabel15.setText(" ");
                   t= false;
                   
               }
               
           }
           
           if(oct>=127 && oct <=191)
           {
               
               ns=(int)(Math.pow(2, 14))-2;
               if(sn<=ns)
               {
                   t= true;
                   jLabel15.setText(" ");
               }
               else 
               {
                   if(sn>=ns && sn<((int)(Math.pow(2,32))-2))
                       jLabel15.setText(" ");
                   t= false;
                   
               }
           }
           if(oct>191 && oct <=223)
           {
               
               ns=(int)(Math.pow(2, 6))-2;
               if(sn<=ns)
               {
                   t= true;
                   jLabel15.setText(" ");
               }
               else 
               {
                   if(sn>=ns && sn<((int)(Math.pow(2,32))-2))
                       jLabel15.setText("");
                   t= false;
                   
               }
           }
           
           System.out.println(ns);
           return t;
    }
     
     private boolean valhost() 
     {
        boolean t = false;
         String ip=jTextField1.getText();
        String snet2=jTextField2.getText();
           String oct1 = null;
           int pto;
           pto=ip.indexOf(".");
           oct1=ip.substring(0, pto);
           
           int oct;
           oct=Integer.parseInt(oct1);
           int sn;
           sn=Integer.parseInt(snet2);
           int ns = 0;
           if(sn==0)
               t=false;
           else{
        if(oct>0 && oct <=127)
           {
               
               ns=(int)(Math.pow(2,22))-2;
               
               if(sn<=ns)
               {
                   
                   t= true;
                   jLabel15.setText(" ");
               }
               else 
               {
                   if(sn>=ns && sn<((int)(Math.pow(2,32))-2))
                       jLabel15.setText(" ");
                   t= false;
                   
               }
               
           }
           
           if(oct>=127 && oct <=191)
           {
               
               ns=(int)(Math.pow(2, 14))-2;
               if(sn<=ns)
               {
                   t= true;
                   jLabel15.setText(" ");
               }
               else 
               {
                   if(sn>=ns && sn<((int)(Math.pow(2,32))-2))
                       jLabel15.setText(" ");
                   t= false;
                   
               }
           }
           if(oct>191 && oct <=223)
           {
               
               ns=(int)(Math.pow(2, 6))-2;
               if(sn<=ns)
               {
                   t= true;
                   jLabel15.setText(" ");
               }
               else 
               {
                   if(sn>=ns && sn<((int)(Math.pow(2,32))-2))
                       jLabel15.setText(" ");
                   t= false;
                   
               }
           }
           }
           System.out.println(ns);
           return t;
    }
     
    private boolean valprefijo() 
     {
        boolean t = false;
         String ip=jTextField1.getText();
        String prefijo=jTextField2.getText();
           String oct1 = null;
           int pto;
           pto=ip.indexOf(".");
           oct1=ip.substring(0, pto);
           //System.out.println(oct1);
           int oct;
           oct=Integer.parseInt(oct1);
           int sn;
           sn=Integer.parseInt(prefijo);
           int ns = 0;
        if(oct>0 && oct <=127)
           {
               if(sn<31 && sn>=8 && sn!=9)
               {
                   
                   t= true;
                   jLabel15.setText(" ");
               }
               else 
               {
                   if(sn>0 && sn<8)
                       jLabel15.setText(" ");
                   t= false;
                   
               }
               
           }
           
           if(oct>=127 && oct <=191)
           {
               if(sn<31 && sn>=16 && sn!=17)
               {
                   t= true;
                   jLabel15.setText(" ");
               }
               else 
               {
                   if(sn>0 && sn<16)
                       jLabel15.setText(" ");
                   t= false;
                   
               }
           }
           if(oct>191 && oct <=223)
           {
               if(sn<31 && sn>=24 && sn!=25)
               {
                   t= true;
                   jLabel15.setText(" ");
               }
               else 
               {
                   if(sn>0 && sn<24)
                       jLabel15.setText(" ");
                   t= false;
                   
               }
           }
           
           System.out.println(ns);
           return t;
    }
     
     private void calcxsub() 
     {
         String snet2=jTextField2.getText();
         int sn;
         sn=Integer.parseInt(snet2);
         int b=0;
         int i=0;
         String ip=jTextField1.getText();
         String oct1 = null;
         int pto;
         pto=ip.indexOf(".");
         oct1=ip.substring(0, pto);
         int host, prefijo;
         //System.out.println(oct1);
         int oct;
         oct=Integer.parseInt(oct1);
           
         for(i=0;i<32;i++)
         {
             b=(int)Math.pow(2, i);
             if(b-2>=sn)
             {
                 break;
             }
         }
         jLabel8.setText(String.valueOf(b-2)); 
         
           //System.out.println(oct);
           if(oct>0 && oct <=127)
           {
               if(sn==0){
                   jLabel8.setText("0");
                   jLabel9.setText("16777214");
                   jLabel10.setText("8");
               }
               else{
               prefijo =8+i;
               jLabel10.setText(String.valueOf(prefijo));
               host=(int)Math.pow(2, 32-prefijo)-2;
                if(host<0)
                   host=0;
               jLabel9.setText(String.valueOf(host));
               }
           }
          
           if(oct>=127 && oct <=191)
           {
               if(sn==0){
                   jLabel8.setText("0");
                   jLabel9.setText("65536");
                   jLabel10.setText("16");
               }
              prefijo =16+i;
               jLabel10.setText(String.valueOf(prefijo));
               host=(int)Math.pow(2, 32-prefijo)-2;
                if(host<0)
                   host=0;
               jLabel9.setText(String.valueOf(host));
           }
           if(oct>191 && oct <=223)
           {
               if(sn==0){
                   jLabel8.setText("0");
                   jLabel9.setText("254");
                   jLabel10.setText("24");
               }
               
               prefijo =24+i;
               jLabel10.setText(String.valueOf(prefijo));
               host=(int)Math.pow(2, 32-prefijo)-2;
               if(host<0)
                   host=0;
               jLabel9.setText(String.valueOf(host));
           }
                   
     }
     
     private void calcxhost() 
     {
         String snet2=jTextField2.getText();
         int sn;
         sn=Integer.parseInt(snet2);
         int b=0;
         int i=0;
         String ip=jTextField1.getText();
         String oct1 = null;
         int pto;
         pto=ip.indexOf(".");
         oct1=ip.substring(0, pto);
         int sub, prefijo;
         //System.out.println(oct1);
         int oct;
         oct=Integer.parseInt(oct1);
           
         for(i=0;i<32;i++)
         {
             b=(int)Math.pow(2, i);
             if(b-2>=sn)
             {
                 break;
             }
         }
         jLabel9.setText(String.valueOf(b-2)); 
         
           //System.out.println(oct);
           if(oct>0 && oct <=127)
           {
               prefijo =32-(8+i);
               jLabel10.setText(String.valueOf(prefijo+8));
               sub=(int)Math.pow(2, prefijo)-2;
               if(sub<0)
                   sub=0;
               jLabel8.setText(String.valueOf(sub));
           }
          
           if(oct>=127 && oct <=191)
           {
              prefijo =32-(16+i);
               jLabel10.setText(String.valueOf(prefijo+16));
               sub=(int)Math.pow(2, prefijo)-2;
               if(sub<0)
                   sub=0;
               jLabel8.setText(String.valueOf(sub));
           }
           if(oct>191 && oct <=223)
           {
               prefijo =32-(24+i);
               jLabel10.setText(String.valueOf(prefijo+24));
               sub=(int)Math.pow(2, prefijo)-2;
               if(sub<0)
                   sub=0;
               jLabel8.setText(String.valueOf(sub));
           }
           
         
     }
     
      private void calcxprefijo() 
     {
         String sprefijo=jTextField2.getText();
         int sn;
         sn=Integer.parseInt(sprefijo);
         int b=0;
         int i=0;
         String ip=jTextField1.getText();
         String oct1 = null;
         int pto;
         pto=ip.indexOf(".");
         oct1=ip.substring(0, pto);
         int sub, prefijo,host;
         //System.out.println(oct1);
         int oct;
         oct=Integer.parseInt(oct1);
           
         
         jLabel10.setText(sprefijo); 
         
           //System.out.println(oct);
           if(oct>0 && oct <=127)
           {
               prefijo =sn-8;
               if(sn==8)
                   sub=1;
               else
               sub=(int)Math.pow(2, prefijo)-2;
               if(sub<0)
                   sub=0;
               jLabel8.setText(String.valueOf(sub));
               if(sn==31)
                   host=1;
               else
               host=(int)Math.pow(2, 32-sn)-2;
               jLabel9.setText(String.valueOf(host));
           }
          
           if(oct>=127 && oct <=191)
           {
              prefijo =sn-16;
               sub=(int)Math.pow(2, prefijo)-2;
               if(sub<0)
                   sub=0;
               jLabel8.setText(String.valueOf(sub));
               host=(int)Math.pow(2, 32-sn)-2;
               if(host<0)
                   host=0;
               jLabel9.setText(String.valueOf(host));
           }
           if(oct>191 && oct <=223)
           {
               prefijo =sn-24;
               sub=(int)Math.pow(2, prefijo)-2;
               if(sub<0)
                   sub=0;
               jLabel8.setText(String.valueOf(sub));
               host=(int)Math.pow(2, 32-sn)-2;
               if(host<0)
                   host=0;
               jLabel9.setText(String.valueOf(host));
           }
           
         
     }
      
      private void tsub()
     {
         String s=jTextField1.getText();
         String[] mete=new String [84000000];
         int o;
         String ss;
         int j;
         int a = 0,b = 0,c = 0,d;
         int nums=0, pto=0;
                    for(o=0;o< s.length();o++)
                    {
                        if(s.charAt(o) == '.')
                        {
                            pto++;
                            //System.out.println(nums);
                            ss=s.substring(o-nums, o);
                            nums=0;
                            j=Integer.parseInt(ss);
                            //System.out.println(j);
                            switch(pto)
                            {
                                case 1:
                                    a=j;
                                break;
                                    
                                case 2:
                                    b=j;
                                break;
                                
                                case 3:
                                    c=j;
                                break;
                                    
                                case 4:
                                    d=j;
                                break;    
                            
                            }
                        }
                        else
                        {
                            nums++;
                        }
                    }  
                    String cuatro;
                    cuatro=s.substring(s.lastIndexOf(".")+1, s.length());
                    d=Integer.parseInt(cuatro);
                    System.out.println("elem "+ a +"."+b+"."+c+"."+d);
                    
                int bits=0;
                //String mete;
                int per=0;
                    
                switch(clas){
                    case 1:
                        bits=prefix-8;
                        b=0;
                        c=0;
                        d=0;
                        if(bits>0 && bits<9)
                        {
                            int potencia=8-bits;
                            int n;
                            //System.out.println(snet);
                            for (n=0;n<snet;n++){
                                b=b+(int)Math.pow(2, potencia);
                                //System.out.println(b);
                                mete[per]=String.valueOf(a)+"."+String.valueOf(b)+"."+String.valueOf(c)+"."+String.valueOf(d);
                                System.out.println(mete[per]);
                                per++;
                                /*String sq = "insert into subred values('"+mete+"')";
                                ResultSet consulta = db.consulta('U', sq);*/
                                jTable1.setModel(makeModel(mete, tablet1,per));
        
                            }
                               
                        }
                        System.out.println("bits "+bits);
                        
                        if(bits>=9 && bits<17)
                        {
                            int potencia=16-bits;
                            int n=0,r=0,lim;
                            
                            for (r=0;r<255;r++){
                                b++;
                                if(n==0)
                                {
                                }
                                else
                                {
                                    mete[per]=String.valueOf(a)+"."+String.valueOf(b)+"."+String.valueOf(c)+"."+String.valueOf(d);
                                System.out.println(mete[per]);
                                per++;
                                }
                                if(r==254)
                                {
                                lim=(int)Math.pow(2, bits-8)-2;
                                }
                                else
                                {
                                lim=(int)Math.pow(2, bits-8)-1;
                                }
                                
                            for (n=0;n<lim;n++){
                                c=c+(int)Math.pow(2, potencia);
                                //System.out.println(c);
                                mete[per]=String.valueOf(a)+"."+String.valueOf(b)+"."+String.valueOf(c)+"."+String.valueOf(d);
                                System.out.println(mete[per] );
                                per++;
                                
                                /*String sq = "insert into subred values('"+mete+"')";
                                ResultSet consulta = db.consulta('U', sq);*/
                                
                            }
                            c=0;
                            
                            }
                            jTable1.setModel(makeModel(mete, tablet1,per));
                        }
                        
                        if(bits>=17 && bits<25)
                        {
                            int potencia=24-bits;
                            int n=0,r=0,w=0,lim;
                            for(w=0;w<255;w++)
                            {
                                b++;
                            for (r=0;r<255;r++){
                                c++;
                                if(n==0)
                                {
                                }
                                else
                                {
                                    mete[per]=String.valueOf(a)+"."+String.valueOf(b)+"."+String.valueOf(c)+"."+String.valueOf(d);
                                System.out.println(mete[per]);
                                per++;
                                }
                                if(r==254)
                                {
                                lim=(int)Math.pow(2, bits-16)-2;
                                }
                                else
                                {
                                lim=(int)Math.pow(2, bits-16)-1;
                                }
                                
                            for (n=0;n<lim;n++){
                                d=d+(int)Math.pow(2, potencia);
                                //System.out.println(d);
                                mete[per]=String.valueOf(a)+"."+String.valueOf(b)+"."+String.valueOf(c)+"."+String.valueOf(d);
                                System.out.println(mete[per]);
                                per++;
                                
                                /*String sq = "insert into subred values('"+mete+"')";
                                ResultSet consulta = db.consulta('U', sq);*/
                                
                            }
                            d=0;
                            
                            }
                            c=0;
                            }
                            jTable1.setModel(makeModel(mete, tablet1,per));
                            
                        }
                        
                    break;
                    case 2:
                        bits=prefix-16;
                        
                        
                        c=0;
                        d=0;
                        System.out.println("bits "+bits);
                        if(bits>0 && bits<9)
                        {
                            int potencia=8-bits;
                            int n;
                            //System.out.println(snet);
                            for (n=0;n<snet;n++){
                                c=c+(int)Math.pow(2, potencia);
                                //System.out.println(b);
                                mete[per]=String.valueOf(a)+"."+String.valueOf(b)+"."+String.valueOf(c)+"."+String.valueOf(d);
                                System.out.println(mete[per]);
                                per++;
                                /*String sq = "insert into subred values('"+mete+"')";
                                ResultSet consulta = db.consulta('U', sq);*/
                                jTable1.setModel(makeModel(mete, tablet1,per));
        
                            }
                               
                        }
                        if(bits>=9 && bits<17)
                        {
                            int potencia=16-bits;
                            int n=0,r=0,lim;
                            
                            for (r=0;r<255;r++){
                                c++;
                                if(n==0)
                                {
                                }
                                else
                                {
                                    mete[per]=String.valueOf(a)+"."+String.valueOf(b)+"."+String.valueOf(c)+"."+String.valueOf(d);
                                System.out.println(mete[per]);
                                per++;
                                }
                                if(r==254)
                                {
                                lim=(int)Math.pow(2, bits-8)-2;
                                }
                                else
                                {
                                lim=(int)Math.pow(2, bits-8)-1;
                                }
                                
                            for (n=0;n<lim;n++){
                                d=d+(int)Math.pow(2, potencia);
                                //System.out.println(d);
                                mete[per]=String.valueOf(a)+"."+String.valueOf(b)+"."+String.valueOf(c)+"."+String.valueOf(d);
                                System.out.println(mete[per]);
                                per++;
                                
                                /*String sq = "insert into subred values('"+mete+"')";
                                ResultSet consulta = db.consulta('U', sq);*/
                                
                            }
                            d=0;
                            
                            }
                            jTable1.setModel(makeModel(mete, tablet1,per));
                        }
                                             
                        
                    break;
                    case 3:
                        d=0;
                        bits=prefix-24;
                        
                        if(bits>0 && bits<9)
                        {
                            d=0;
                           int potencia=8-bits;
                            int n;
                            //System.out.println(snet);
                            for (n=0;n<snet;n++){
                                d=d+(int)Math.pow(2, potencia);
                                //System.out.println(b);
                                mete[per]=String.valueOf(a)+"."+String.valueOf(b)+"."+String.valueOf(c)+"."+String.valueOf(d);
                                System.out.println(mete[per]);
                                per++;
                                /*String sq = "insert into subred values('"+mete+"')";
                                ResultSet consulta = db.consulta('U', sq);*/
                                jTable1.setModel(makeModel(mete, tablet1,per));
        
                            }
                               
                        }
                        
                    break;
                }   
                                                                      
     }
      
}