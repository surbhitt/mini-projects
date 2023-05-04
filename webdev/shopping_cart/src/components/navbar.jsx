
import React from 'react';

// since we want to display the total of counter
// we need the counter 
// this is not possible since navbar is not a parent of counter
// to achieve this we have to raise the state to a higher level
// from where navbar can access it

// this is a stateless functional component 
const Navbar = ({totalCounters}) => {


    return (
        <nav className="navbar navbar-light bg-light">
            <div className="container-fluid">
                <span className="navbar-brand mb-0 h1">
                    Navbar
                    <span className="badge badge-pill badge-secondary">{totalCounters}</span>
                </span>
            </div>
        </nav>
    )
}

/* this is a class
class Navbar extends Component {
    state = {}
    render () {
        return (
            <nav className="navbar navbar-light bg-light">
                <div className="container-fluid">
                    <span className="navbar-brand mb-0 h1">
                        Navbar
                        <span className="badge badge-pill badge-secondary">{this.props.totalCounters}</span>
                    </span>
                </div>
            </nav>
        )
    }
}*/

export default Navbar;