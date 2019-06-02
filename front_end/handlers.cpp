#include "handlers.hpp"

using namespace std;

SignupHandler::SignupHandler(Network* _net) : RequestHandler(), net(_net) {} 

Response* SignupHandler::callback(Request *req) {
    string username = req->getBodyParam("username");
    string password1 = req->getBodyParam("pwd1");
    string password2 = req->getBodyParam("pwd2");
    string email = req->getBodyParam("email");
    int age = stoi(req->getBodyParam("Age"));
    string publisher = "false";
    if(req->getBodyParam("publisher") == "on")
        publisher = "true";

    if(!(password1 == password2)) {
        Response *res = Response::redirect("/signup");
        return res;
    }
    try {
        net->signup_user(email, username, password1, age, publisher);
        int cookie = net->make_sessionId();
        Response *res = Response::redirect("/");
        res->setSessionId(to_string(cookie));
        return res;
    } catch (Logedin ex){
        Response *res = Response::redirect("/error?error=You_are_already_loggedin");
        return res;
    } catch (DuplicateUser ex) {
        Response *res = Response::redirect("/error?error=This_username_already_exists");
        return res;
    }
}
LoginHandler::LoginHandler(Network* _net) : RequestHandler(), net(_net) {}

Response* LoginHandler::callback(Request *req) {
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    try {
        net->login_user(username, password);
        Response* res = Response::redirect("/");
        res->setSessionId(to_string(net->get_sessionId()));
        return res;
    } catch(BadRequest ex){
        Response* res = Response::redirect("/error?error=Wrong_username_or_password");
        return res;
    } catch (Logedin ex){
        Response *res = Response::redirect("/error?error=loggedin");
        return res;
    }

}

LogoutHandler::LogoutHandler(Network* _net) : RequestHandler(), net(_net) {}

Response* LogoutHandler::callback(Request *req) {
    try {
        net->logout();
        Response *res = Response::redirect("/");
        res->setSessionId("");
        return res;
    } catch(BadRequest ex) {
        Response *res = Response::redirect("/");
        res->setSessionId("");
        return res;
    }
}

ErrorHandler::ErrorHandler(string filePath) : TemplateHandler(filePath){}

map<string, string> ErrorHandler::handle(Request *req) {
  map<string, string> context;
  string error = req->getQueryParam("error");
  context["error"] = error;
  return context;
}

HomeHandler::HomeHandler(Network* _net) : RequestHandler(), net(_net) {}

Response* HomeHandler::callback(Request* req) {
    Response* res = new Response;
    vector<vector<string>> table;
    map<string, string> param;
    
    if(!(net->get_dir_to_filter_by() == ""))
        param["director"] = net->get_dir_to_filter_by();
    net->set_dir_filter("");
    if(net->publisher_is_logged())
        table = net->get_published(param);
    else
        table = net->get_movies(param);
        

    res->setHeader("Content-Type", "text/html");
    stringstream body;
    body 
<<"<!DOCTYPE html>"
<<" <html>"
<<"     <head>"
<<"         <title>Home</title>"
<<"         <link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' media='all'>"
<<"     </head>"
<<"     <body>"
<<"         <nav class='navbar navbar-expand-sm bg-dark navbar-dark fixed-top'>"
<<"             <ul class='navbar-nav mr-auto'>"
<<"                 <li class='nav-item active'>"
<<"                     <a class='nav-link' href='/signup'>Sign up</a>"
<<"                 </li>"
<<" "
<<"                 <li class='nav-item'>"
<<"                     <a class='nav-link' href='/profile'>Profile</a>"
<<"                 </li>"
<<" "
<<"                 <li class='nav-item'>"
<<"                     <a class='nav-link' href='/login'>Login</a>"
<<"                 </li>"
<<" "
<<"                 <li class='nav-item'>"
<<"                     <form method='POST' action='/logout'>"
<<"                         <button class='btn btn-danger'>Logout</button>"
<<"                     </form>"
<<"                 </li>"
<<"                 <span class='navbar-text'></span>"
<<"             </ul>"
<<"             <form class='form-inline my-2 my-lg-0' action='/' method='POST'>"
<<"                  <input class='form-control mr-sm-2' type='text' placeholder='filter director' required='required' name='director'>"
<<"                  <button class='btn btn-success' type='submit'>Filter</button>"
<<"             </form>"
<<"         </nav><br><br><br>"
<<"         <div class='container'>"    
<<"         <table class='table'>"
<<"         <thead class='thead-dark'>"
<<"             <tr>"
<<"                 <th>FirstnameName</th>"
<<"                 <th>Director</th>"
<<"                 <th>Length</th>"
<<"                 <th>Rate</th>"
<<"                 <th>Price</th>"
<<"                 <th>Year</th>"
<<"                 <th>DELETE</th>"
<<"                 <th>Detail</th>"
<<"             </tr>"
<<"         </thead>"
<<"         <tbody>";
    for(int i = 0; i < table.size(); i++) {
        body<<"<tr>";
        body<<"<th>"<<table[i][TABLE_NAME]<<"</th>";
        body<<"<th>"<<table[i][TABLE_DIRECTOR]<<"</th>";
        body<<"<th>"<<table[i][TABLE_LENGTH]<<"</th>";
        body<<"<th>"<<table[i][TABLE_RATE]<<"</th>";
        body<<"<th>"<<table[i][TABLE_PRICE]<<"</th>";
        body<<"<th>"<<table[i][TABLE_YEAR]<<"</th>";
        body<<"<th>"
        <<"     <form method='post' action='/deleteMovie?filmId="<<table[i][TABLE_ID]<<"'>";
        if(net->publisher_is_logged()){
            body<<" <button type='submit' class='btn btn-outline-danger btn-sm' >Delete</button>";
        } else {
            body<<" <button type='submit' class='btn btn-outline-danger btn-sm' disabled>Delete</button>";           
        }
        body
        <<"     </form></th>"
        <<"     <th>"
        <<"     <form method='post' action='/viewMovie?filmId="<<table[i][TABLE_ID]<<"'>"
        <<"         <button type='submit' class='btn btn-outline-info btn-sm' >Detail</button>"
        <<"     </form></th>"
        <<"</tr>";
    }
    if(net->publisher_is_logged()){
        body
        <<"</tbody></table>"
        <<"<form method='get' action='/addFilm'>"
        <<"    <button type='submit' class='btn btn-success btn-lg' align='middle'>ADD FILM</button>"
        <<"</form>";
    }
    body
<<"     </div>"
<<"   </body>"
<<" </html>";
    res->setBody(body.str());
    return res;
}


AddFilmHandler::AddFilmHandler(Network* _net) : RequestHandler(), net(_net) {}

Response* AddFilmHandler::callback(Request *req) {
    net->add_movie(req->getBodyParam("name"), stoi(req->getBodyParam("year")), stoi(req->getBodyParam("length")), stoi(req->getBodyParam("price")), req->getBodyParam("summary"), req->getBodyParam("director"));
    Response* res = Response::redirect("/");
    return res;
}


FilterHandler::FilterHandler(Network* _net) : RequestHandler(), net(_net) {}

Response* FilterHandler::callback(Request *req) {
    net->set_dir_filter(req->getBodyParam("director"));
    Response* res = Response::redirect("/");
    return res;
}

DeleteHandler::DeleteHandler(Network* _net) : RequestHandler(), net(_net) {}

Response* DeleteHandler::callback(Request *req) {
    net->delete_film(stoi(req->getQueryParam("filmId")));
    Response* res = Response::redirect("/");
    return res;
}

ProfileHandler::ProfileHandler(Network* _net) : RequestHandler(), net(_net) {}

Response* ProfileHandler::callback(Request *req) {
    Response* res = new Response;
    vector<vector<string>> table;
    map<string, string> param;
    try{
        table = net->get_purchased(param);
    } catch (PermissionDenied ex){
        res = Response::redirect("/error?error=You_need_to_be_loggedin");
        return res;
    }
    stringstream body;
    res->setHeader("Content-Type", "text/html");
    body 
<<"<!DOCTYPE html>"
<<" <html>"
<<"     <head>"
<<"         <title>Profile</title>"
<<"         <link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' media='all'>"
<<"     </head>"
<<"     <body>"
<<"         <nav class='navbar navbar-expand-sm bg-dark navbar-dark fixed-top'>"
<<"             <ul class='navbar-nav mr-auto'>"
<<"                 <li class='nav-item active'>"
<<"                     <a class='nav-link' href='/'>Home</a>"
<<"                 </li>"

<<"                 <li class='nav-item'>"
<<"                     <form method='POST' action='/logout'>"
<<"                         <button class='btn btn-danger'>Logout</button>"
<<"                     </form>"
<<"                 </li>"
<<"                 <span class='navbar-text'></span>"
<<"             </ul>"
<<"             <form class='form-inline my-2 my-lg-0' action='/profile' method='POST'>"
<<"                  <input class='form-control mr-sm-2' type='number' placeholder='money' name='money'>"
<<"                  <button class='btn btn-success' type='submit'>Get</button>"
<<"             </form>"
<<"         </nav><br><br><br>"
<<"         <div class='container'>"    
<<"         <table class='table'>"
<<"         <thead class='thead-dark'>"
<<"             <tr>"
<<"                 <th>FirstnameName</th>"
<<"                 <th>Director</th>"
<<"                 <th>Length</th>"
<<"                 <th>Rate</th>"
<<"                 <th>Price</th>"
<<"                 <th>Year</th>"
<<"                 <th>Detail</th>"
<<"             </tr>"
<<"         </thead>"
<<"         <tbody>";
    cout<<table.size()<<endl;
    for(int i = 0; i < table.size(); i++) {

        body<<"<tr>";
        body<<"<th>"<<table[i][TABLE_NAME]<<"</th>";
        body<<"<th>"<<table[i][TABLE_DIRECTOR]<<"</th>";
        body<<"<th>"<<table[i][TABLE_LENGTH]<<"</th>";
        body<<"<th>"<<table[i][TABLE_RATE]<<"</th>";
        body<<"<th>"<<table[i][TABLE_PRICE]<<"</th>";
        body<<"<th>"<<table[i][TABLE_YEAR]<<"</th>";

            body<<"<th>"
            <<"     <form method='post' action='/viewMovie?filmId="<<table[i][TABLE_ID]<<"'>"
            <<"         <button type='submit' class='btn btn-outline-info btn-sm'>Detail</button>"
            <<"     </form></th>";
        body<<"</tr>";
    }
    body
<<"     </div>"
<<"   </body>"
<<" </html>";
    res->setBody(body.str());
    return res;
}

MoneyHandler::MoneyHandler(Network* _net) : RequestHandler(), net(_net) {}

Response* MoneyHandler::callback(Request *req) {
    if(!(req->getBodyParam("money") == ""))
        net->get_money_user(stoi(req->getBodyParam("money")));
    Response* res = Response::redirect("/profile");
    return res;
}


DetailHandler::DetailHandler(Network* _net) : RequestHandler(), net(_net) {}

Response* DetailHandler::callback(Request *req) {
    cout<<"laaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"<<endl;
    Response* res = new Response();
    stringstream body;
    map<string, string> data = net->get_movie_base_data(stoi(req->getQueryParam("filmId"))); 


    res->setHeader("Content-Type", "text/html");

    body
<<"    <!DOCTYPE html>"
<<"<html lang='en'>"
<<"    <head>"
<<"        <title>Movie Detail</title>"
<<"        <meta charset='utf-8'>"
<<"        <meta name='viewport' content='width=device-width, initial-scale=1'>"
<<"        <link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css'>"
<<"    </head>"
<<"    <body>"
<<"        <nav class='navbar navbar-expand-sm bg-dark navbar-dark fixed-top'>"
<<"            <ul class='navbar-nav'>"
<<"                <li class='nav-item active'>"
<<"                    <a class='nav-link' href='/'>Home</a>"
<<"                </li>"
<<""
<<"                <li class='nav-item'>"
<<"                    <a class='nav-link' href='/profile'>Profile</a>"
<<"                </li>"
<<""
<<"                <li class='nav-item mr-auto'>"
<<"                    <form method='POST' action='/logout'>"
<<"                        <button class='btn btn-danger' type='submit'>logout</button>"
<<"                    </form>"
<<"                </li>"
<<"    "
<<""
<<"                <span class='navbar-text'></span>"
<<"            </ul>"
<<"        </nav>"
<<"        <br><br><br><br>"
<<"    <div class='container' align='middle'>"
<<"    <ul class='list-group list-group-flush'>"
<<"        <li class=\"list-group-item\"><h1>"
<<              data[B_NAME]
<<"        </h1></li>"
<<""
<<"        <li class=\"list-group-item\"><h3>Directed By:<br>"
<<              data[B_DIRECTOR]
<<"        </h3></li>"
<<"    "
<<"        <li class=\"list-group-item\"><h5>Summary:"
<<              data[B_SUMMARY]
<<"        </h5><br></li>"
<<""
<<"        <li class=\"list-group-item\">"
<<"            <div class=\"row\">"
<<"                <div class=\"col\" >Price : "
<<                      data[B_PRICE]
<<"                </div>"
<<"                <div class=\"col\" >Year :"
<<                      data[B_YEAR]
<<"                </div>"
<<"                <div class=\"col\" >Length : "
<<                      data[B_LENGTH]
<<"                </div>"
<<"            </div>"
<<"        </li>"
<<""
<<"        <li class=\"list-group-item\"><h6>Rate:"
<<              data[B_RATE]
<<"        </h6></li>"
<<"            "
<<"    </ul>"
<<"    <form action='/buyFilm?filmId='>"
<<"        <br><button class='btn btn-success'>Buy Movie</button>    "
<<"    </form>"
<<"    </div><br><br>"
<<"    <div class='container' align='middle'>"
<<"    <h4>Recommended</h4>"
<<"    </div><br>"
<<"    <div class='container'>"
<<"        <table class='table'>"
<<"            <thead class='thead-dark'>"
<<"                <tr>"
<<"                    <th>Name</th>"
<<"                    <th>Length</th>"
<<"                    <th>Director</th>"
<<"                </tr>   "
<<"            </thead>"
<<"            <tbody>"
<<"            <tr>"
<<"                <td>John</td>"
<<"                <td>Doe</td>"
<<"                <td>john@example.com</td>"
<<"            </tbody>"
<<"            </table>"
<<"        </div>"
<<"    </body>"
<<"</html>";
    res->setBody(body.str());
    return res;
}
