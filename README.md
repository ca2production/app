# app

app is core repository of **ca2** framework

ca2 is an all-purpose multi-platform framework and set of libraries written in C++ language to help developers create great apps for users.


## Open "love" Sample App for Windows Desktop

1. Use/Create non-system folder, that will be called here **root folder**, with name of project like C:\create_love_sample_app or C:\users\username\create_love_sample_app (please, don't use spaces or special characters or parent folders with spaces or special characters).
2. Immediatelly below **root folder**, create new empty folder named **"app"**. 
3. Clone https://github.com/ca2/app.git into this **app** folder.
4. Immediatelly below **root folder**, create new empty folder named **"nodeapp"**. 
5. Clone https://github.com/ca2/nodeapp-windows.git into this **nodeapp** folder. (Notice that nodeapp folder doesn't follow convention of naming the folder where repository will be cloned exactly the same name as the original repository: the **<dash-platform>** ("-windows") suffix is stripped from it).
6. Immediatelly below **root folder**, create any new folder(s) related to the project. In this case, for our sample tutorial, a folder named **"app-sample"**. 
7. Clone to this(these) folder(s), the respective ca2-framework-compatible repositories related to the ca2-based app of interest. In our case, clone https://github.com/ca2/app-sample.git into **app-sample** folder.
8. At main project specific folder, in our case, **app-sample**, under **seed/metaseed** subfolder, find desired **"Visual Studio"** solution file to open. In this case **app_sample_simple.sln**.
9. Play with it.


## Create App "masterapp" based on Sample App "simple" for Windows Desktop

1. Follow procedure described at **"Open "simple" Sample App for Windows Desktop"** from steps 1. to 6., for the **"simple"** project you want to base your **"myapp"** on, and for the **Sample** repository (in these steps, **app-sample**) where lies this **"simple"** project you want your **"myapp"** app based on.
2. Someway create copy of **Sample** repository folder structure and data at your local storage. You can do it by forking **Sample** (in these steps, **app-sample**) project and putting under **app-myeffort** (you can name **app-myeffort** at your will, avoiding conflicts with other possibly or already existing names) folder at your local storage.
3. Duplicate related items at subfolders **appmatter**, **appseed** and **seed/metaseed** inside **app-myeffort**
a. duplicate **"simple"** project folder at **appmatter** to **"myapp"** folder;
b. **appseed**, and;
c. **seed/metaseed.

for the sample you want your app based on.



Built with tbs in <3
