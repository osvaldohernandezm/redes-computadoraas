package calculadorip;


public class Validation{
    

    public boolean isInt(String s){
      boolean comprobado;
        try{
            Integer.parseInt(s);
            comprobado = true;
        }
        catch(Exception e){
            comprobado = false;
        }
      return comprobado;
    }

    public boolean isNumber(String s){
        boolean comprobado;
        try{
            Double.parseDouble(s);
            comprobado = true;
        }
        catch(Exception e){
            comprobado = false;
        }
        return comprobado;
    }

    public boolean isIP(String s){
        boolean checked= true;
        String [] sc = {"a","A","b","B","c","C","d","D","e","E","f","F","g","G","h","H","i","I","j","J","k","K",
            "l","L","m","M","n","N","ñ","Ñ","o","O","p","P","q","Q","r","R","s","S","t","T","u","U","v","V","W",
            "w","x","X","y","Y","z","Z","!","\"","$","%","&","/","(",")","=","'","?","\\","¿","¡","*","+","~",
            "{","}","[","]","^",",",";",":","_","<",">","|","°","¬","@"};
        try{
            int i = 0;
            int o;
            int u;
            String ss;
            int j;
            //int []sip = null;
            
        while (i<sc.length){
            if (s.contains(sc[i])){
                checked = false;
                i = 99;
            }
            else{
                if(s.startsWith("."))
                {
                    checked=false;
                    
                }
                else 
                { 
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
                            //sip[pto-1]=j;
                            if(j>255)
                            {
                                  checked=false;  
                                  break;
                            }
                            
                        }
                        else
                        {
                            nums++;
                        }
                    }
                    if(nums!=0 && pto!=0)
                    {
                    if(nums<=3 && pto==3)
                        checked=true;
                    else
                        checked=false;
                    }
                    else
                        checked=false;
                
                }   
                i++;
            }
        }
        }
        catch(Exception e){
            checked = false;
        }
        return checked;
    }


    public boolean checkLenght(String s, char mode, int length){
        boolean checked;
        switch (mode){
            case '=':
                if(s.length()==length){
                    checked = true;
                }
                else{
                    checked = false;
                }
            break;
            case '>':
                if(s.length()>=length){
                    checked = true;
                }
                else{
                    checked = false;
                }
            break;
            case '<':
                if (s.length()<= length){
                    checked = true;
                }
                else{
                    checked = false;
                }
            break;
            default:
                checked = false;
            break;
        }
        return checked;

    }

    public boolean checkEmail(String s){
        boolean checked = false;
        if (s.contains("@")){
           String [] domains = {".com" , ".org", ".net", ".mx" ,".es",".us",".vg",".fr",".cl",".ar",".info",".tk",".gob",
           ".gov",".biz",".ly",".edu",".eu"};
           int i = 0;
           while (i<domains.length){
               if (s.endsWith(domains[i])){
                   checked = true;
                   i = 99;
               }
               else{
                   checked = false;
                   i++;
               }
           }
        }
        else{
            checked = false;
        }
        return checked;
    }

    public boolean checkSpecialChars(String s){
        boolean checked = false;
        String [] sc = {"!","\"","$","%","&","/","(",")","=","'","?","\\","¿","¡","*","+","~","{","}","[","]","^",",",";",
        ":",".","_","<",">","|","°","¬","@"};
        int i = 0;
        while (i<sc.length){
            if (s.contains(sc[i])){
                checked = false;
                i = 99;
            }
            else{
                checked = true;
                i++;
            }

        }

        return checked;
    }

    public boolean checkOnlyLetters(String s){
        boolean checked = false;
        String [] numbers = {"1","2","3","4","5","6","7","8","9","0"};
        int i = 0;
        while (i<numbers.length){
            if(s.contains(numbers[i]) || checkSpecialChars(s) == false){
                checked = false;
                i = 99;
            }
            else{
                checked = true;
                i++;
            }
        }
        return checked;
    }

    public boolean checkNotVoid(String s){
        boolean checked = false;
        if(s.length()<=0){
            checked = false;
        }
        else{
            checked = true;


        }
        return checked;
    }

}
