import entity.User;

import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;

@ManagedBean
@SessionScoped
public class UserController {

    private String id;

    private User user;

    @EJB
    private UserHandlerBean userHandlerBean;
    @EJB
    private FruitHandlerBean fruitHandlerBean;

    public UserController() {

    }

    public String registerUser() {

        setUser(userHandlerBean.createUser(id));

        return "saladmanager?faces-redirect=true";
    }

    public String retrieveUser() {
        setUser(userHandlerBean.findUser(id));

        return "saladmanager?faces-redirect=true";
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }
}