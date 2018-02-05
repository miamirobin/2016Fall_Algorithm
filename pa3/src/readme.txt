1. 學號： b03208022 
2. 姓名： 李友岐
3. 使用之程式語言：< C++ >
4. 使用之編譯器：< Mac terminal g++ >
5. 檔案壓縮方式: <zip>
6. 各檔案說明：
	 main.cpp : 純文字主程式
	 parser.cpp  : parser檔案
	 parser.h  :  parser檔案
	 readme.txt : 敘述如何編譯與執行程式
	 report.docx ： 程式報告
        verify.cpp : 驗證程式
        router: Executable binary
7. 編譯方式說明：        	
   主程式： 我用mac的terminal,先到主程式所在之資料夾
          然後輸入 g++ main.cpp parser.cpp -o router
	   即可產生一個執行檔 router
   
   驗證程式：輸入 g++ verify.cpp -o verify
           即可產生一個執行檔 verify
   
           
8. 執行、使用方式說明：
   主程式：
   編譯完成後，在檔案目錄下會產生一個 router 的執行檔
   執行檔的命令格式為：
   ./router <input file name> <output file name>

   驗證程式：執行檔名為verify，命令格式與主程式相同
   ./verify <input file name> <output file name>
           
