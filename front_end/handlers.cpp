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

        if(net->publisher_is_logged()){
            body<<"<th>"
            <<"     <form method='post' action='/deleteMovie?filmId="<<table[i][TABLE_ID]<<"'>"
            <<"         <button type='submit' class='btn btn-outline-danger btn-sm'>Delete</button>"
            <<"     </form></th>";
        }
        body<<"</tr>";
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