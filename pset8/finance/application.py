import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set !!!!!!!!!!!
# if not os.environ.get("API_KEY"): !!!!!!!!!!!
#     raise RuntimeError("API_KEY not set") !!!!!!!!!!!

# db.execute("INSERT INTO users (username, hash, cash) VALUES ('arlei', '123', '999')")
# db.execute("DELETE FROM users WHERE 1=1")

# db.execute("DROP TABLE transactions")

# Create table transactions if it not exists
db.execute("""
    CREATE TABLE IF NOT EXISTS transactions (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        user_id INTEGER NOT NULL,
        symbol VARCHAR(4) NOT NULL,
        name VACHAR(255) NOT NULL,
        quantity INTEGER NOT NULL,
        price FLOAT NOT NULL,
        action VARCHAR(4) NOT NULL,
        Timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
        )""")




@app.route("/")
@login_required
def index():
    rows = db.execute("""
        SELECT
            symbol,
            name,
            sum(quantity) as quantity
        FROM
            transactions 
        GROUP BY
            symbol,
            name
    """)
    

    for row in rows:
        quote = lookup(row["symbol"])
        row["price"] = quote["price"]
        total = row["price"] * float(row["quantity"])
        row["total"] = usd(total)
        row["price"] = usd(row["price"])
 

    """Show portfolio of stocks"""
    return render_template("portifolio.html", rows = rows)
    # return apology("TODO") !!!!!!!!!!!


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        quantity = request.form.get("quantity")
        quote = lookup(symbol)
        if quote:
            db.execute("""
            INSERT INTO 
                transactions (user_id, symbol, name, quantity, price, action) 
            VALUES 
                (:user_id, :symbol, :name, :quantity, :price, :action)
            """, 
                user_id = session["user_id"], 
                symbol = quote["symbol"], 
                name = quote["name"], 
                quantity = quantity, 
                price = quote["price"], 
                action = "buy"
            )
            session["action"] = "buy"
            return redirect("/")
        else:
            invalid = True
            return render_template("/buy.html", invalid= invalid)
    """Buy shares of stock"""
    return apology("TODO")


@app.route("/history")
@login_required
def history():
    # select data from transactions
    rows = db.execute("SELECT * FROM transactions ORDER BY timestamp DESC")
    # return html histoy passing the rows
    return render_template("/history.html", rows = rows)
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "GET":
        return render_template("/quote.html", invalid = False)
    else:
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if quote:
            return render_template("quoteResult.html", name=quote["name"], symbol=quote["symbol"], price=usd(quote["price"]))
        else:
            return render_template("/quote.html", invalid = True)
    """Get stock quote."""
    return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("/register.html")
    else:
        username = request.form.get("username")
        password = generate_password_hash(request.form.get("password"))

        # verify if the username already exists
        rows = db.execute("SELECT * FROM users WHERE username=:username", username = username)
        print(len(rows))
        # if select returns 0 we can register the user
        if len(rows) == 0:
            # insert the register into users table
            db.execute("INSERT INTO users (username, hash, cash) VALUES (:username, :password, 10000)", username = username, password = password)
            # send user back to login page
            return redirect("/login")
        else:
            # inform that the username already exists
            invalid = True
            return render_template("register.html", invalid=invalid)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        return render_template("sell.html")
    else:
        symbol = request.form.get("symbol")
        quantity = request.form.get("quantity")
        quote = lookup(symbol)
        db.execute("""
        INSERT INTO 
            transactions (user_id, symbol, name, quantity, price, action) 
        VALUES 
            (:user_id, :symbol, :name, :quantity, :price, :action)
        """, 
            user_id = session["user_id"], 
            symbol = quote["symbol"], 
            name = quote["name"], 
            quantity = quantity, 
            price = quote["price"], 
            action = "sell"
        )
        session["action"] = "sell"
        return redirect("/")
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
